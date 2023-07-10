# TekSH
Version 1.5.5
<img src="https://t.bkit.co/w_64925db39b56d.gif" />
-----------------

## Description

TekSH is a small project that would like to grow bigger. Its aim is to implement a shell and add functionality.
You are welcome to join us !

-----------------

## Installation

```
git clone https://github.com/SizzleUnrlsd/TekSH
```
```
cd Teksh && make
```
```
./teksh
```

-----------------

## Usage

```
./teksh --version

████████╗███████╗██╗  ██╗███████╗██╗  ██╗
╚══██╔══╝██╔════╝██║ ██╔╝██╔════╝██║  ██║
   ██║   █████╗  █████╔╝ ███████╗███████║
   ██║   ██╔══╝  ██╔═██╗ ╚════██║██╔══██║
   ██║   ███████╗██║  ██╗███████║██║  ██║
   ╚═╝   ╚══════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝
1.5.5

```

```
•[/home/TekSH]{ main } pwd
•[/home]{ main } ls ; cd ~
•[/home/TekSH]{ main } cd -
•[/home/TekSH]{ main } touch toto ; ls -alt > toto ; cat toto
•[/home/TekSH]{ main } ls | cat | cat | cat > toto
•[/home/TekSH]{ main } turtle
```

-----------------

## Shell-integrated command

- [ ] [Builtins]

```
•[/home/TekSH]{ main } alias l ls -alt
•[/home/TekSH]{ main } cd
•[/home/TekSH]{ main } echo
•[/home/TekSH]{ main } env
•[/home/TekSH]{ main } exit
•[/home/TekSH]{ main } set
•[/home/TekSH]{ main } setenv
•[/home/TekSH]{ main } unset
•[/home/TekSH]{ main } unsetenv
•[/home/TekSH]{ main } history
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
- [ ] [Raspeberry Pi OS (Test in development)]

Tests are carried out for each distribution. Run the tests with the following command:

```
make tests_build
```

For verbosity:

```
make tests_build_verbose
```

Other distributions will be tested soon !

## Compatible architecture

- [ ] [x86_64]
- [ ] [ARM]

Integration tests on different architectures are coming soon.

## Compilation

Teksh is compiled with gcc. You can find the compilation flags in the following folder:

```
Shell
├── flag_makefile
│   ├── cflags.txt
│   ├── ldlibs.txt
│   ├── memory_flags.txt
│   └── nodeadcode.txt
```

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
- [ ] Improving tests and Github Action.
- [ ] File descriptor management

**Note :** This roadmap is subject to change and will be updated as the project evolves.

## Recently Added/Patched 

- [ ] Add : job control
- [ ] fix : multiple-pipe
- [ ] Fix : Output management outside tty
- [ ] Improve : Improved update system

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
You can contact us by e-mail :

```
hugo.payet@epitech.eu
```
