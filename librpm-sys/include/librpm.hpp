// librpm.hpp: Wrapper for librpm header files to be passed to bindgen
//
// See "Using the RPM Library" section of "Chapter 15. Programming RPM with C"
// of the Fedora RPM Guide (Draft 0.1):
//
// https://docs.fedoraproject.org/en-US/Fedora_Draft_Documentation/0.1/html/RPM_Guide/ch-programming-c.html#id737996
//
// We include the header files listed in tables 16-1 and 16-2 (see
// header-specific notes in comments below).
//
// ## Why does this file have a `.hpp` extension (i.e. why a C++ binding?)
//
// This file has a `.hpp` extension to signal to bindgen to treat it (and
// the rest of the librpm header files) as C++. Though that may seem a little
// crazy, there's actually a good reason for it.
//
// Some of RPM's header files (namely `/usr/include/popt.h`, which is included
// by several important librpm headers including `rpmbuild.h`, `rpmsign.h`, and
// `rpmspec.h) define pointer typedefs for structs with the same name as the
// structs they point to, which is valid in C but not valid in C++, and
// likewise also not valid in bindgen's generated bindings for the same reason:
// they map to type aliases with the same name as the types they're aliasing.
//
// See: https://github.com/rust-lang-nursery/rust-bindgen/issues/1252
//
// By naming this file with a .hpp extension we instruct bindgen to produce a
// C++ binding instead of a C one, which triggers macro-based gating (i.e.
// `#ifdef __cplusplus`) throughout librpm's headers.
//
// Treating the headers as C++ prevents them from defining these sorts of type
// aliases and allows us to bind to more of librpm than we can using C.
//
// Additionally it resolved bindgen-generated test failures for memory
// alignment, allowing us to generate a low-level binding for all parts of
// RPM worth caring about (although FWIW that should be fixed soon in bindgen
// now that `#[repr(align(N))]` is stable.

/** RPM configuration */
#include <rpm/rpmlib.h> // RIP Steve Taylor
#include <rpm/rpmmacro.h> // Macros control RPM configuration

/** RPM sub-system header files (from Table 16-1, omitting popt.h) */
#include <rpm/rpmdb.h> // RPM database access
#include <rpm/rpmio.h> // RPM input/output routines

/** RPM data object header files (from Table 16-2) */
#include <rpm/header.h> // Package headers
#include <rpm/rpmds.h> // Dependency sets
#include <rpm/rpmfi.h> // File information
#include <rpm/rpmts.h> // Transaction sets
#include <rpm/rpmte.h> // Transaction elements (packages)
#include <rpm/rpmtypes.h> // RPM data types
