# TekSH
Version 1.1.2
<img src="https://t.bkit.co/w_64925db39b56d.gif" />
-----------------

## Description
TekSH is a small project that would like to grow bigger. Its aim is to implement a shell and add functionality.
You are welcome to join us !

-----------------

## Installation

```
git clone https://github.com/SizzleUnrlsd/TekSH
make
./teksh
```

-----------------

## Usage
```
pwd
ls ; cd ~
cd -
touch toto ; ls -alt > toto ; cat toto
ls | cat | cat | cat > toto
turtle
```

-----------------

## Shell-integrated command

- [ ] [Builtins]

```
alias
cd
echo
env
exit
set
setenv
unset
unsetenv
history
```

- [ ] [Plugins]

You can also create your own orders with the plugins. Use the turtle command:

```
•[/home] turtle

          _____     ____
         /      \  |  o |
        |        |/ ___\|
        |_________/
        |_| | |_| |

```

This command was added to the code quite simply.
You can therefore develop your software and integrate it into the shell in this section:

```
Shell
├── plugins
│   └── add_ons
│       ├── loader.c
│       ├── Makefile
│       └── plugins
│           ├── plugin_display.c
│           └── plugin_turtle.c
```

The language supported is C. C++ and Python will follow soon.

## Update

When a new version of teksh is available, this message appears:
    
```
████████╗███████╗██╗  ██╗███████╗██╗  ██╗
╚══██╔══╝██╔════╝██║ ██╔╝██╔════╝██║  ██║
   ██║   █████╗  █████╔╝ ███████╗███████║
   ██║   ██╔══╝  ██╔═██╗ ╚════██║██╔══██║
   ██║   ███████╗██║  ██╗███████║██║  ██║
   ╚═╝   ╚══════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝
You're not up to date,
Update to the latest version? Y / n
$>
```

You will then be prompted to update the repository.
A new update system will be coming soon.

-----------------

## Compatible distribution

- [ ] [Fedora]
- [ ] [Debian]
- [ ] [Archlinux]

Tests are carried out for each distribution. Run the tests with the following command:

```
make tests_build
```

Other distributions will be tested soon !

## Compatible architecture

- [ ] [x86_64]
- [ ] [ARM]

Integration tests on different architectures are coming soon.

## Debug

By default, the shell catches errors linked to SIGSEGV. You can disable this mode by recompiling with :

```
make debug
```

Internal shell errors that are caught are stored in an 'error_prompt_cmd' file.

```
Shell
├── mini_dump
│   └── error_promt_cmd
```

You can help by sharing this file in case of a bug.

## Roadmap

- [ ] Addition of a new update system
- [ ] Support for other distribution
- [ ] Addition of scripting functions
- [ ] Integration of C++ and Python for plugins
- [ ] Patch the 'echo' command to support advanced options and special character escapes
- [ ] Integration of different themes in the shell to customise appearance and style
- [ ] Improved memory utilisation
- [ ] Advanced input/output management
- [ ] Add architecture tests.

**Note :** This roadmap is subject to change and will be updated as the project evolves.

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
You can contact us by e-mail :

```
hugo.payet@epitech.eu
```
