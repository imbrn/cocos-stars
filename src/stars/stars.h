#ifndef STARS_STARS_H
#define STARS_STARS_H

#include <cocos2d.h>
#include <ui/CocosGUI.h>
#include <functional>
#include <vector>

namespace stars {

class StarsBuilder;

///
/// Stars class.
///
class Stars: public cocos2d::ui::Widget {
  friend class StarsBuilder;
  unsigned int amount_;
  float gap_;
  std::string inactive_star_path_;
  std::string active_star_path_;
  std::vector<cocos2d::ui::ImageView*> inactive_stars_;
  std::vector<cocos2d::ui::ImageView*> active_stars_;

protected:
  Stars(const StarsBuilder &builder);

public:
  virtual ~Stars() {}

  void ShowInactive(unsigned int index);
  void HideInactive(unsigned int index);
  void ShowAllInactives();
  void HideAllInactives();

  void ShowActive(unsigned int index);
  void HideActive(unsigned int index);
  void ShowAllActives();
  void HideAllActives();
  
  virtual bool init() override;

  cocos2d::ui::ImageView *get_inactive_star(std::function<bool(unsigned int, cocos2d::ui::ImageView*)> criteria);
  cocos2d::ui::ImageView *get_inactive_star(unsigned int index);
  cocos2d::ui::ImageView *get_inactive_star(const cocos2d::Point &location);

  cocos2d::ui::ImageView *get_active_star(std::function<bool(unsigned int, cocos2d::ui::ImageView*)> criteria);
  cocos2d::ui::ImageView *get_active_star(unsigned int index);
  cocos2d::ui::ImageView *get_active_star(const cocos2d::Point &location);

protected:
  virtual cocos2d::ui::ImageView *CreateInactiveStar(unsigned int index) const;
  virtual cocos2d::ui::ImageView *CreateActiveStar(unsigned int index) const;
  virtual void onSizeChanged() override;

private:
  void RecicleStars();

  void RecicleInactiveStars();
  void RemoveInactiveStars();
  void AddInactiveStars();
  void AddInactiveStar(unsigned int index);
  void PositionInactiveStars();

  void RecicleActiveStars();
  void RemoveActiveStars();
  void AddActiveStars();
  void AddActiveStar(unsigned int index);
  void PositionActiveStars();

  void Fit(unsigned int index, cocos2d::ui::ImageView *star);
  void Align(unsigned int index, cocos2d::ui::ImageView *star);

  cocos2d::Rect get_slot_area(unsigned int index) const;
  cocos2d::Point get_slot_origin(unsigned int index) const;
  cocos2d::Size get_slot_size(unsigned int index) const;
  cocos2d::Size get_available_size() const;
};

///
/// StarsBuilder class.
///
class StarsBuilder {
  friend class Stars;
  unsigned int amount_ = 3;
  float gap_ = 4;
  std::string inactive_star_path_ = "inactive_star.png";
  std::string active_star_path_ = "active_star.png";

public:
  StarsBuilder &set_amount(unsigned int amount);
  StarsBuilder &set_gap(float gap);
  StarsBuilder &set_inactive_star_path(const std::string &inactive_star_path);
  StarsBuilder &set_active_star_path(const std::string &active_star_path);
  Stars *Build() const;
};

}

#endif
