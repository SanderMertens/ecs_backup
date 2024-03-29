/*
                                   )
                                  (.)
                                  .|.
                                  | |
                              _.--| |--._
                           .-';  ;`-'& ; `&.
                          \   &  ;    &   &_/
                           |"""---...---"""|
                           \ | | | | | | | /
                            `---.|.|.|.---'

 * This file is generated by bake.lang.c for your convenience. Headers of
 * dependencies will automatically show up in this file. Include bake_config.h
 * in your main project file. Do not edit! */

#ifndef ECS_BACKUP_BAKE_CONFIG_H
#define ECS_BACKUP_BAKE_CONFIG_H

/* Headers of public dependencies */
#include <flecs.h>
#include <flecs_components_transform.h>
#include <flecs_components_geometry.h>
#include <flecs_components_graphics.h>
#include <flecs_components_input.h>
#include <flecs_systems_sdl2.h>

/* Headers of private dependencies */
#ifdef ECS_BACKUP_IMPL
/* No dependencies */
#endif

/* Convenience macro for exporting symbols */
#ifndef ECS_BACKUP_STATIC
  #if ECS_BACKUP_IMPL && (defined(_MSC_VER) || defined(__MINGW32__))
    #define ECS_BACKUP_EXPORT __declspec(dllexport)
  #elif ECS_BACKUP_IMPL
    #define ECS_BACKUP_EXPORT __attribute__((__visibility__("default")))
  #elif defined _MSC_VER
    #define ECS_BACKUP_EXPORT __declspec(dllimport)
  #else
    #define ECS_BACKUP_EXPORT
  #endif
#else
  #define ECS_BACKUP_EXPORT
#endif

#endif

