#include "stars.h"

namespace stars {

Stars::Stars(const StarsBuilder &builder):
    amount_(builder.amount_), gap_(builder.gap_),
    inactive_star_path_(builder.inactive_star_path_),
    active_star_path_(builder.active_star_path_) {}

cocos2d::ui::ImageView *Stars::CreateInactiveStar(unsigned int index) const {
  return cocos2d::ui::ImageView::create(inactive_star_path_);
}

cocos2d::ui::ImageView *Stars::CreateActiveStar(unsigned int index) const {
  return cocos2d::ui::ImageView::create(active_star_path_);
}

void Stars::ShowInactive(unsigned int index) {
  get_inactive_star(index)->setVisible(true);
}

void Stars::HideInactive(unsigned int index) {
  get_inactive_star(index)->setVisible(false);
}

void Stars::ShowAllInactives() {
  for (unsigned int i = 0; i < amount_; i++)
    ShowInactive(i);
}

void Stars::HideAllInactives() {
  for (unsigned int i = 0; i < amount_; i++)
    HideInactive(i);
}

void Stars::ShowActive(unsigned int index) {
  get_active_star(index)->setVisible(true);
}

void Stars::HideActive(unsigned int index) {
  get_active_star(index)->setVisible(false);
}

void Stars::ShowAllActives() {
  for (unsigned int i = 0; i < amount_; i++)
    ShowActive(i);
}

void Stars::HideAllActives() {
  for (unsigned int i = 0; i < amount_; i++)
      HideActive(i);
}

bool Stars::init() {
  if (!cocos2d::ui::Widget::init())
    return false;
  RecicleStars();
  return true;
}

void Stars::RecicleStars() {
  RecicleInactiveStars();
  RecicleActiveStars();
}

void Stars::RecicleInactiveStars() {
  RemoveInactiveStars();
  AddInactiveStars();
}

void Stars::RemoveInactiveStars() {
  for (auto star : inactive_stars_)
    removeChild(star);
  inactive_stars_.clear();
}

void Stars::AddInactiveStars() {
  for (unsigned int i = 0; i < amount_; i++)
    AddInactiveStar(i);
}

void Stars::AddInactiveStar(unsigned int index) {
  auto star = CreateInactiveStar(index);
  addChild(star, 0);
  inactive_stars_.push_back(star);
}

void Stars::PositionInactiveStars() {
  for (unsigned int i = 0; i < amount_; i++) {
    auto star = get_inactive_star(i);
    Fit(i, star);
    Align(i, star);
  }
}

void Stars::RecicleActiveStars() {
  RemoveActiveStars();
  AddActiveStars();
}

void Stars::RemoveActiveStars() {
  for (auto star : active_stars_)
    removeChild(star);
  active_stars_.clear();
}

void Stars::AddActiveStars() {
  for (unsigned int i = 0; i < amount_; i++)
    AddActiveStar(i);
}

void Stars::AddActiveStar(unsigned int index) {
  auto star = CreateActiveStar(index);
  addChild(star, 1);
  active_stars_.push_back(star);
}

void Stars::PositionActiveStars() {
  for (unsigned int i = 0; i < amount_; i++) {
    auto star = get_active_star(i);
    Fit(i, star);
    Align(i, star);
  }
}

void Stars::Fit(unsigned int index, cocos2d::ui::ImageView *star) {
  auto slot_size = get_slot_size(index);
  float horz = slot_size.width / star->getContentSize().width;
  float vert = slot_size.height / star->getContentSize().height;
  star->setScale(MIN(horz, vert));
}

void Stars::Align(unsigned int index, cocos2d::ui::ImageView *star) {
  auto slot_area = get_slot_area(index);
  star->setAnchorPoint({0.5, 0.5});
  star->setPosition({slot_area.getMidX(), slot_area.getMidY()});
}

void Stars::onSizeChanged() {
  cocos2d::ui::Widget::onSizeChanged();
  PositionInactiveStars();
  PositionActiveStars();
}

cocos2d::Rect Stars::get_slot_area(unsigned int index) const {
  return { get_slot_origin(index), get_slot_size(index) };
}

cocos2d::Point Stars::get_slot_origin(unsigned int index) const {
  auto size = get_slot_size(index);
  float x = (size.width * index) + (gap_ * index);
  return { x, 0 };
}

cocos2d::Size Stars::get_slot_size(unsigned int index) const {
  auto available = get_available_size();
  return { available.width / amount_, available.height };
}

cocos2d::Size Stars::get_available_size() const {
  float w = getContentSize().width - ((amount_-1) * gap_);
  float h = getContentSize().height;
  return { w, h };
}

cocos2d::ui::ImageView *Stars::get_inactive_star(std::function<bool(unsigned int, cocos2d::ui::ImageView*)> criteria) {
  for (unsigned int i = 0; i < amount_; i++)
    if (criteria(i, inactive_stars_[i])) return inactive_stars_[i];
  return nullptr;
}

cocos2d::ui::ImageView *Stars::get_inactive_star(unsigned int index) {
  return inactive_stars_[index];
}

cocos2d::ui::ImageView *Stars::get_inactive_star(const cocos2d::Point &location) {
  return get_inactive_star([location](unsigned int index, cocos2d::ui::ImageView *star) -> bool {
    return star->getBoundingBox().containsPoint(location);
  });
}

cocos2d::ui::ImageView *Stars::get_active_star(std::function<bool(unsigned int, cocos2d::ui::ImageView*)> criteria) {
  for (unsigned int i = 0; i < amount_; i++)
    if (criteria(i, active_stars_[i])) return active_stars_[i];
  return nullptr;
}

cocos2d::ui::ImageView *Stars::get_active_star(unsigned int index) {
  return active_stars_[index];
}

cocos2d::ui::ImageView *Stars::get_active_star(const cocos2d::Point &location) {
  return get_active_star([location](unsigned int index, cocos2d::ui::ImageView *star) {
    return star->getBoundingBox().containsPoint(location);
  });
}

StarsBuilder &StarsBuilder::set_amount(unsigned int amount) {
  amount_ = amount;
  return *this;
}

StarsBuilder &StarsBuilder::set_gap(float gap) {
  gap_ = gap;
  return *this;
}

StarsBuilder &StarsBuilder::set_inactive_star_path(const std::string &inactive_star_path) {
  inactive_star_path_ = inactive_star_path;
  return *this;
}

StarsBuilder &StarsBuilder::set_active_star_path(const std::string &active_star_path) {
  active_star_path_ = active_star_path;
  return *this;
}

Stars *StarsBuilder::Build() const {
  Stars *stars = new Stars(*this);
  if (stars->init()) {
    stars->autorelease();
    return stars;
  } else {
    delete stars;
    return nullptr;
  }
}

}
