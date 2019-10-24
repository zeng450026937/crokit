#include "yealink/rtvc/binding/desktop_media_list_base.h"

#include <set>

#include "base/bind.h"
#include "base/task/post_task.h"
#include "base/threading/thread_task_runner_handle.h"
#include "yealink/rtvc/binding/desktop_media_list_observer.h"

namespace rtvc {

DesktopMediaListBase::DesktopMediaListBase(base::TimeDelta update_period)
    : update_period_(update_period), weak_factory_(this) {}

DesktopMediaListBase::~DesktopMediaListBase() {}

void DesktopMediaListBase::SetUpdatePeriod(base::TimeDelta period) {
  DCHECK(!observer_);
  update_period_ = period;
}

void DesktopMediaListBase::SetThumbnailSize(
    const ThumbnailSize& thumbnail_size) {
  thumbnail_size_ = thumbnail_size;
}

void DesktopMediaListBase::SetViewDialogWindowId(DesktopMediaID dialog_id) {
  view_dialog_id_ = dialog_id;
}

void DesktopMediaListBase::StartUpdating(DesktopMediaListObserver* observer) {
  DCHECK(!observer_);

  observer_ = observer;
  Refresh();
}

int DesktopMediaListBase::GetSourceCount() const {
  return sources_.size();
}

const DesktopMediaList::Source& DesktopMediaListBase::GetSource(
    int index) const {
  DCHECK_GE(index, 0);
  DCHECK_LT(index, static_cast<int>(sources_.size()));
  return sources_[index];
}

const std::vector<DesktopMediaList::Source>& DesktopMediaListBase::GetSources()
    const {
  return sources_;
}

DesktopMediaID::Type DesktopMediaListBase::GetMediaListType() const {
  return type_;
}

DesktopMediaListBase::SourceDescription::SourceDescription(
    DesktopMediaID id,
    const base::string16& name)
    : id(id), name(name) {}

void DesktopMediaListBase::UpdateSourcesList(
    const std::vector<SourceDescription>& new_sources) {
  // Notify observer when there was no new source captured.
  if (new_sources.empty()) {
    observer_->OnSourceUnchanged(this);
    return;
  }

  typedef std::set<DesktopMediaID> SourceSet;
  SourceSet new_source_set;
  for (size_t i = 0; i < new_sources.size(); ++i) {
    new_source_set.insert(new_sources[i].id);
  }
  // Iterate through the old sources to find the removed sources.
  for (size_t i = 0; i < sources_.size(); ++i) {
    if (new_source_set.find(sources_[i].id) == new_source_set.end()) {
      sources_.erase(sources_.begin() + i);
      observer_->OnSourceRemoved(this, i);
      --i;
    }
  }
  // Iterate through the new sources to find the added sources.
  if (new_sources.size() > sources_.size()) {
    SourceSet old_source_set;
    for (size_t i = 0; i < sources_.size(); ++i) {
      old_source_set.insert(sources_[i].id);
    }

    for (size_t i = 0; i < new_sources.size(); ++i) {
      if (old_source_set.find(new_sources[i].id) == old_source_set.end()) {
        sources_.insert(sources_.begin() + i, Source());
        sources_[i].id = new_sources[i].id;
        sources_[i].name = new_sources[i].name;
        observer_->OnSourceAdded(this, i);
      }
    }
  }
  DCHECK_EQ(new_sources.size(), sources_.size());

  // Find the moved/changed sources.
  size_t pos = 0;
  while (pos < sources_.size()) {
    if (!(sources_[pos].id == new_sources[pos].id)) {
      // Find the source that should be moved to |pos|, starting from |pos + 1|
      // of |sources_|, because entries before |pos| should have been sorted.
      size_t old_pos = pos + 1;
      for (; old_pos < sources_.size(); ++old_pos) {
        if (sources_[old_pos].id == new_sources[pos].id)
          break;
      }
      DCHECK(sources_[old_pos].id == new_sources[pos].id);

      // Move the source from |old_pos| to |pos|.
      Source temp = sources_[old_pos];
      sources_.erase(sources_.begin() + old_pos);
      sources_.insert(sources_.begin() + pos, temp);

      observer_->OnSourceMoved(this, old_pos, pos);
    }

    if (sources_[pos].name != new_sources[pos].name) {
      sources_[pos].name = new_sources[pos].name;
      observer_->OnSourceNameChanged(this, pos);
    }
    ++pos;
  }
}

// void DesktopMediaListBase::UpdateSourceThumbnail(DesktopMediaID id,
//                                                  const gfx::ImageSkia& image)
//                                                  {
//   for (size_t i = 0; i < sources_.size(); ++i) {
//     if (sources_[i].id == id) {
//       sources_[i].thumbnail = image;
//       observer_->OnSourceThumbnailChanged(this, i);
//       break;
//     }
//   }
// }

void DesktopMediaListBase::ScheduleNextRefresh() {
  if (!observer_->ShouldScheduleNextRefresh(this))
    return;
  base::ThreadTaskRunnerHandle::Get()->PostDelayedTask(
      FROM_HERE,
      base::BindOnce(&DesktopMediaListBase::Refresh,
                     weak_factory_.GetWeakPtr()),
      update_period_);
}

// static
// uint32_t DesktopMediaListBase::GetImageHash(const gfx::Image& image) {
//   SkBitmap bitmap = image.AsBitmap();
//   uint32_t value = base::Hash(bitmap.getPixels(), bitmap.computeByteSize());
//   return value;
// }

}  // namespace rtvc
