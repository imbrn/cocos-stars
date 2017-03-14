#ifndef STARS_RATING_ANIMATION_H
#define STARS_RATING_ANIMATION_H

#include <cocos2d.h>
#include "stars.h"
#include "rating_shine_sound.h"

namespace stars {

class RatingAnimationBuilder;

///
/// RatingAnimation class.
///
class RatingAnimation {
  friend class RatingAnimationBuilder;
  Stars *stars_ = nullptr;
  RatingShineSound *shine_sound_ = nullptr;
  float shine_duration_;
  float delay_;
  unsigned int rating_;

private:
  RatingAnimation(const RatingAnimationBuilder &builder);

public:
  virtual ~RatingAnimation() {}
  cocos2d::FiniteTimeAction *AsAction();
  
private:
  cocos2d::FiniteTimeAction *CreateAction();
  void CreateRatingActions(cocos2d::Vector<cocos2d::FiniteTimeAction*> &actions);
  cocos2d::FiniteTimeAction *CreateRatingAction(unsigned int index);
  cocos2d::FiniteTimeAction *CreateShine(unsigned int index);
  cocos2d::FiniteTimeAction *CreateSetVisible(unsigned int index);
  cocos2d::FiniteTimeAction *CreateShineSound(unsigned int index);
  void PlayShineSoundEffect(unsigned int star_index);
  cocos2d::FiniteTimeAction *CreateScaleUp(unsigned int index, float duration);
  cocos2d::FiniteTimeAction *CreateScaleDown(unsigned int index, float duration);
  cocos2d::FiniteTimeAction *CreateAutoDestroyAction();
};

///
/// RatingAnimationBuilder class.
///
class RatingAnimationBuilder {
  friend class RatingAnimation;
  Stars *stars_ = nullptr;
  RatingShineSound *shine_sound_ = nullptr;
  float shine_duration_ = 0.15f;
  float delay_ = 0.15f;
  unsigned int rating_ = 3;

public:
  RatingAnimationBuilder(Stars *stars);
  RatingAnimationBuilder &set_shine_sound(RatingShineSound *shine_sound);
  RatingAnimationBuilder &set_shine_duration(float shine_duration);
  RatingAnimationBuilder &set_delay(float delay);
  RatingAnimationBuilder &set_rating(unsigned int rating);
  RatingAnimation *Build() const;
};

}

#endif
