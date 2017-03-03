#include "rating_animation.h"

namespace stars {

RatingAnimation::RatingAnimation(const RatingAnimationBuilder &builder):
    stars_(builder.stars_), shine_duration_(builder.shine_duration_), delay_(builder.delay_),
    rating_(builder.rating_) {}

cocos2d::FiniteTimeAction *RatingAnimation::AsAction() {
  return CreateAction();
}

cocos2d::FiniteTimeAction *RatingAnimation::CreateAction() {
  cocos2d::Vector<cocos2d::FiniteTimeAction*> actions;
  CreateRatingActions(actions);
  actions.pushBack(CreateAutoDestroyAction());
  return cocos2d::Sequence::create(actions);
}

void RatingAnimation::CreateRatingActions(cocos2d::Vector<cocos2d::FiniteTimeAction*> &actions) {
  for (unsigned int i = 0; i < rating_; i++)
    actions.pushBack(CreateRatingAction(i));
}

cocos2d::FiniteTimeAction *RatingAnimation::CreateRatingAction(unsigned int index) {
  float delay = (index < rating_ - 1) ? delay_ : 0;
  return cocos2d::Sequence::create(CreateShine(index), cocos2d::DelayTime::create(delay), nullptr);
}

cocos2d::FiniteTimeAction *RatingAnimation::CreateShine(unsigned int index) {
  return cocos2d::Sequence::create(
    CreateSetVisible(index),
    CreateScaleUp(index, shine_duration_ * 0.4),
    CreateScaleDown(index, shine_duration_ * 0.6),
    nullptr
  );
}

cocos2d::FiniteTimeAction *RatingAnimation::CreateSetVisible(unsigned int index) {
  return cocos2d::CallFunc::create([this, index]() {
    stars_->get_active_star(index)->setVisible(true);
  });
}

cocos2d::FiniteTimeAction *RatingAnimation::CreateScaleUp(unsigned int index, float duration) {
  auto star = stars_->get_active_star(index);
  return cocos2d::TargetedAction::create(star, cocos2d::ScaleBy::create(duration, 1.45f));
}

cocos2d::FiniteTimeAction *RatingAnimation::CreateScaleDown(unsigned int index, float duration) {
  auto star = stars_->get_active_star(index);
  return cocos2d::TargetedAction::create(star, cocos2d::ScaleTo::create(duration, star->getScale()));
}

cocos2d::FiniteTimeAction *RatingAnimation::CreateAutoDestroyAction() {
  return cocos2d::CallFunc::create([this]() {
    delete this;
  });
}

RatingAnimationBuilder::RatingAnimationBuilder(Stars *stars): stars_(stars) {}

RatingAnimationBuilder &RatingAnimationBuilder::set_shine_duration(float shine_duration) {
  shine_duration_ = shine_duration;
  return *this;
}

RatingAnimationBuilder &RatingAnimationBuilder::set_delay(float delay) {
  delay_ = delay;
  return *this;
}

RatingAnimationBuilder &RatingAnimationBuilder::set_rating(unsigned int rating) {
  rating_ = rating;
  return *this;
}

RatingAnimation *RatingAnimationBuilder::Build() const {
  return new RatingAnimation(*this);
}

}
