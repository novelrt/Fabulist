# Fabulist #

A terse, flexible language and runtime for creating and executing visual
novels.

## Project Synopsis ##

This is a rough synopsis of the project structure as it stands today:

### `cli` ###

A small command-line utility for evaluating Fabulist scripts.

### `docs` ###

Project documentation, including this readme :)

### `examples` ###

A not-comprehensive list of examples of Fabulist syntax, used primarily for
testing. As the language is fleshed out, there will be more examples added here.

### `lua` ###

Effectively scratch space, this directory is used for rapid development and
prototyping of Fabulist syntax.

### `src` ###

The implementation of the Fabulist runtime, in ABI-portable C++.

### `thirdparty` ###

Third-party dependencies which are automatically retrieved by CMake.

## Why? ##

During the development of [NovelRT], we evaluated many options and ultimately
decided that none of the existing options completely satisfied our needs:

1. Terseness: Visual novel writers shouldn't feel it necessary to abbreviate
   character names just to get more of the script in view at once.
   Additionally, code should not get in the way of the script when it's not
   necessary.

2. Maintained: Any option chosen should have very few maintenance challenges.

3. Simplicity: The language should be simple to read and write, without
   remembering the meaning of a bunch of symbols.

4. Standalone: The language and runtime shouldn't be attached to an entire game
   engine, as that's the job of [NovelRT].

These are the options we were aware of before setting out on the task to design
our own language, and an explanation of why we felt they did not satisfy our
needs.

### [Ren'Py] ###

1. Terseness: It is well known that authors abbreviate their character names
   because the Ren'Py language is fairly verbose in places. Furthermore, it is
   regularly the case that code and script are entertwined, causing maintenance
   and density issues.

2. Maintained: Ren'Py is absolutely maintained.

3. Simplicity: Ren'Py is fairly simple.

4. Standalone: Ren'Py is mostly attached to the Ren'Py engine, and the work
   necessary to extract it would functionally mean forking the language and
   making our own anyway.

### [Ink] ###

1. Terseness: Ink is fairly terse, keeping a lot of the script in view at once.

2. Maintained: Ink is questionably maintained, as the developers rarely if ever
   respond to GitHub issues, or review PRs. As of writing this, there is a PR
   open that hasn't been merged or closed since 2018. In comparison, the Ink
   package for Unity was last updated in February 2021.

3. Simplicity: Despite Ink's terseness, there are a lot of special symbols and
   syntax constructs that need to be remembered.

4. Standalone: While Ink is "standalone" in that the Ink compiler and engine is
   detached from any game engine in particular, it is functionally tied to
   Unity as this is the only way it is distributed - and it appears most of the
   development effort has moved there.

### [Twine] ###

There are many languages used in Twine. However, they have the same basic
properties:

1. Terseness: Code is regularly interpolated with script - it appears more like
   a language designed for developers rather than authors.

2. Maintained: As there are many different syntaxes, it's hard to say if they
   are maintained. Of the three observed, only two seem to be actively
   maintained.

3. Simplicity: The fact that there are many languages says a lot; having to
   decide which language to use and if it will support all the features needed
   may be overwhelming to beginners.

4. Standalone: Twine's languages appear closely related to the Twine engine,
   which is purely web/JS-based. It does not look like it would be easy to
   separate the two.

## Contributing ##

We're open to contributions from anyone and everyone. If you'd like to chat
with us, feel free to contact us on [Discord].

**NovelRT and everyone contributing (this includes issues, pull requests, the
wiki, Discord in all forms, etc.) must abide by our code of conduct, which can
be found [here][CodeOfConduct]. Instances of abuse, harrassment or
otherwise unacceptable behaviour must either be reported to a NovelRT Developer
via direct message on Discord or by contacting us via
[email][CodeOfConductEmail].**

### Building ###

Before building Fabulist, you need to install some dependencies, and ensure
they can be located by CMake

#### Dependencies ####
1. Lua 5.1 (Version TBD) (Debian-derivatives: `liblua5.1-0-dev`)
2. A C++ compiler supporting C++17 (Debian-derivates: `build-essential`)
3. CMake 3.18 (Debian-derivatives: `cmake`)

#### Instructions ####
Compiling Fabulist should be fairly simple, using commands something like this:
```
mkdir build
cd build
cmake ..
cmake --build . -j
```

### Code style ###

There's no set code style yet, so for now just try to be consistent with the
rest of the code.

## License ##

Copyright (c) 2022 FiniteReality and Contributors.

See [License][LICENSE] for more information.

[NovelRT]: https://github.com/NovelRT/NovelRT
[Ren'Py]: https://www.renpy.org/
[Ink]: https://www.inklestudios.com/ink/
[Twine]: http://twinery.org/
[Discord]: https://discord.novelrt.dev/
[CodeOfConduct]: CODE_OF_CONDUCT.md
[CodeOfConductEmail]: mailto:admin%40novelrt.dev
[License]: LICENSE
