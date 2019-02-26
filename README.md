# winman
TUI "window" manager built on top of termlib

## What is it ?

`Winman` stands for Window Manager. It is used as building blocks to create real TUI (Text User Interface) applications.

It provides `windows`, that can be filled with `widgets`.
Those widgets can be buttons, text, or simpler shapes. In the future there will be some complex widgets, as `frames`, `scrollbars` and other building blocks of window application.

## Why the f. does it exists ?

When it comes to user interfaces, you rarely have the choice but to opt for a desktop environment to beneficiate complex features as multi-window systems. Those solutions are nice but goes heavy on ressources, if you are very limited with a low powered target, connected via SSH.

CLI applications, on the other hand, are often not user friendly for non-developers, and people seems to avoid them. 

`winman` tries to tackle theses issues, via a complex window system, while maintaining a very easy to use API.

Some nice TUI applications exists, like tui-rs (https://github.com/fdehau/tui-rs) for rust, but not many uses a true window system.


## Cool ! Can I use it right now ?

Erm, unfortunately, the project isnt mature enough to be used. You can review the sources and propose some PRs, I would be glad, but you should note that the project is in a very early stage. There are a lot of implementation work to do, as well as various optimisations.


## Oh Okay, When will it be available ?

I am currently shooting for a early release in March 2019.

## Nice ! Good luck then !

Thank you ! I'd love to hear your thoughts about the project by the way. You can contact me on julien.letheno@gmail.com
