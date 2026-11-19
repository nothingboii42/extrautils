#pragma once

#define SHELL_H
#ifndef SHELL_H

void spawn_shell(char type[]);
void block_int(void);
int exec_cmd(char *line[]);

#endif /* -- shell.h -- */
