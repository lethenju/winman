# winman

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/da1bc30a488b4f32a4986dc9f5dbbf39)](https://app.codacy.com/app/lethenju/winman?utm_source=github.com&utm_medium=referral&utm_content=lethenju/winman&utm_campaign=Badge_Grade_Dashboard)


When it comes to user interfaces, you rarely have the choice but to opt for a desktop environment to beneficiate complex features as multi-window systems. Those solutions are nice but goes heavy on ressources, if you are very limited with a low powered target, connected via SSH.

CLI applications, on the other hand, are often not user friendly for non-developers, and people seems to avoid them. 

`winman` tries to tackle theses issues, via a complex window system, while maintaining a very easy to use API.

Some nice TUI applications exists, like tui-rs (https://github.com/fdehau/tui-rs) for rust, but not many uses a true window system.

## Description

`Winman` stands for Window Manager. It is used as building blocks to create real TUI (Text User Interface) applications.

It provides `windows`, that can be filled with `widgets`.
Those widgets can be buttons, text, or simpler shapes. In the future there will be some complex widgets, as `frames`, `scrollbars` and other building blocks of window application.

It can be compared to `ncurses` in the fonctionnalities, but tries to be even more user friendly and have more window-like features

## Usage

You can read and launch the example file to understand how to use the project.
type `make build_and_launch` to build the whole system, the log system server and launch all what is needed.

You can type to modify the windows name, press '0' to change in interwindow mode and move the windows themselves using ZQSD.

Don't hesitate to tweak the example file to better understand what is going on.

I am currently shooting for a early release in March 2019.
