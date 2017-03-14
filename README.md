Cocos Stars
===

[Cocos2d-x](http://cocos2d-x.org/) component for exhibition of rating stars in game endings.

![Stars](docs/stars.gif)

## Features

* Custom stars graphics
* Custom amount of stars
* Rating animation
* Cocos2d-x 3.14 or above

## How to use

By default it expects you to have the following images in your resources path:

* active_star.png
* inactive_star.png

but you can configure whatever sound and images you like.

### Shine sounds

To use shine sounds with the rating animation you need to do the following:

* First you need to implement the interface `audio::RatingShineSound`

* Second, you need to pass your interface to the rating animation builder:

```c++
auto animation = stars::RatingAnimationBuilder(my_stars)
    .set_shine_sound(my_rating_shine_sound_object)
    .Build();
```
