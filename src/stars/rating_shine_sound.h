#ifndef STARS_RATING_SHINE_SOUND_H
#define STARS_RATING_SHINE_SOUND_H

namespace stars {

///
/// RatingShineSound class.
///
class RatingShineSound {
public:
  virtual ~RatingShineSound() {}
  virtual void PlayShineSound(unsigned int star_index) {}
};

}

#endif
