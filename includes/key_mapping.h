#ifndef KEY_MAPPING_H
# define KEY_MAPPING_H

# include <stdlib.h>

/*
** KEY - Special
*/

# define KEY_ESC	53
# define KEY_UP		126
# define KEY_DOWN	125
# define KEY_LEFT	123
# define KEY_RIGHT	124
# define KEY_SPACE	49
# define KEY_SHIFT	257
# define KEY_CMD_L	259
# define KEY_CMD_R	260
# define KEY_CMD	KEY_CMD_L || KEY_CMD_R
# define KEY_CTRL_L	256
# define KEY_CTRL_R	269
# define KEY_CTRL	KEY_CTRL_L || KEY_CTRL_R
# define KEY_ALT_L	261
# define KEY_ALT_R	262
# define KEY_ALT	KEY_ALT_L || KEY_ALT_R

/*
** KEY - Alphabet
*/

# define KEY_A		0
# define KEY_B		11
# define KEY_C		8
# define KEY_D		2
# define KEY_E		14
# define KEY_F		3
# define KEY_G		5
# define KEY_H		4
# define KEY_I		34
# define KEY_J		38
# define KEY_K		40
# define KEY_L		37
# define KEY_M		46
# define KEY_N		45
# define KEY_O		31
# define KEY_P		35
# define KEY_Q		12
# define KEY_R		15
# define KEY_S		1
# define KEY_T		17
# define KEY_U		32
# define KEY_V		9
# define KEY_W		13
# define KEY_X		7
# define KEY_Y		16
# define KEY_Z		6

typedef struct			s_key_dispatch
{
	int					key;
	int					(*fct)(int key, void *param, int release);
}						t_key_dispatch;

int						key_handle(int key, void *param);

#endif /* !KEY_MAPPING_H */

/* EOF */
