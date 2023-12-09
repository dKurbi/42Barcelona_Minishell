/* rlprivate.h -- functions and variables global to the readline library,
		  but not intended for use by applications. */

/* Copyright (C) 1999-2010 Free Software Foundation, Inc.

   This file is part of the GNU Readline Library (Readline), a library
   for reading lines of text with interactive input and history editing.      

   Readline is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Readline is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Readline.  If not, see <http://www.gnu.org/licenses/>.
*/

#if !defined (_RL_PRIVATE_H_)
#define _RL_PRIVATE_H_

#include "rlconf.h"	/* for VISIBLE_STATS */
#include "rlstdc.h"
#include "posixjmp.h"	/* defines procenv_t */

/*************************************************************************
 *									 *
 * Convenience definitions						 *
 *									 *
 *************************************************************************/

#define EMACS_MODE()		(rl_editing_mode == emacs_mode)
#define VI_COMMAND_MODE()	(rl_editing_mode == vi_mode && _rl_keymap == vi_movement_keymap)
#define VI_INSERT_MODE()	(rl_editing_mode == vi_mode && _rl_keymap == vi_insertion_keymap)

#ifndef _WIN32
#define RL_CHECK_SIGNALS() \
	do { \
	  if (_rl_caught_signal) _rl_signal_handler (_rl_caught_signal); \
	} while (0)
#else
#define RL_CHECK_SIGNALS()
#endif

/*************************************************************************
 *									 *
 * Global structs undocumented in texinfo manual and not in readline.h   *
 *									 *
 *************************************************************************/
/* search types */
#define RL_SEARCH_ISEARCH	0x01		/* incremental search */
#define RL_SEARCH_NSEARCH	0x02		/* non-incremental search */
#define RL_SEARCH_CSEARCH	0x04		/* intra-line char search */

/* search flags */
#define SF_REVERSE		0x01
#define SF_FOUND		0x02
#define SF_FAILED		0x04
#define SF_CHGKMAP		0x08

typedef struct  __rl_search_context
{
  int type;
  int sflags;

  char *search_string;
  int search_string_index;
  int search_string_size;

  char **lines;
  char *allocated_line;    
  int hlen;
  int hindex;

  int save_point;
  int save_mark;
  int save_line;
  int last_found_line;
  char *prev_line_found;

  UNDO_LIST *save_undo_list;

  Keymap keymap;	/* used when dispatching commands in search string */
  Keymap okeymap;	/* original keymap */

  int history_pos;
  int direction;

  int lastc;
#if defined (HANDLE_MULTIBYTE)
  char mb[MB_LEN_MAX];
#endif

  char *sline;
  int sline_len;
  int sline_index;

  char  *search_terminators;
} _rl_search_cxt;

/* Callback data for reading numeric arguments */
#define NUM_SAWMINUS	0x01
#define NUM_SAWDIGITS	0x02
#define NUM_READONE	0x04

typedef int _rl_arg_cxt;

/* A context for reading key sequences longer than a single character when
   using the callback interface. */
#define KSEQ_DISPATCHED	0x01
#define KSEQ_SUBSEQ	0x02
#define KSEQ_RECURSIVE	0x04

typedef struct __rl_keyseq_context
{
  int flags;
  int subseq_arg;
  int subseq_retval;		/* XXX */
  Keymap dmap;

  Keymap oldmap;
  int okey;
  struct __rl_keyseq_context *ocxt;
  int childval;
} _rl_keyseq_cxt;

/* vi-mode commands that use result of motion command to define boundaries */
#define VIM_DELETE	0x01
#define VIM_CHANGE	0x02
#define VIM_YANK	0x04

/* various states for vi-mode commands that use motion commands.  reflects
   RL_READLINE_STATE */
#define VMSTATE_READ	0x01
#define VMSTATE_NUMARG	0x02

typedef struct __rl_vimotion_context
{
  int op;
  int state;
  int flags;		/* reserved */
  _rl_arg_cxt ncxt;
  int numeric_arg;
  int start, end;	/* rl_point, rl_end */
  int key, motion;	/* initial key, motion command */
} _rl_vimotion_cxt;

/* fill in more as needed */
/* `Generic' callback data and functions */
typedef struct __rl_callback_generic_arg 
{
  int count;
  int i1, i2;
  /* add here as needed */
} _rl_callback_generic_arg;

typedef int _rl_callback_func_t PARAMS((_rl_callback_generic_arg *));

/*************************************************************************
 *									 *
 * Global functions undocumented in texinfo manual and not in readline.h *
 *									 *
 *************************************************************************/

/*************************************************************************
 *									 *
 * Global variables undocumented in texinfo manual and not in readline.h *
 *									 *
 *************************************************************************/

/* complete.c */
READLINE_DLL_IMPEXP int rl_complete_with_tilde_expansion;
#if defined (VISIBLE_STATS)
READLINE_DLL_IMPEXP int rl_visible_stats;
#endif /* VISIBLE_STATS */

/* readline.c */
READLINE_DLL_IMPEXP int rl_line_buffer_len;
READLINE_DLL_IMPEXP int rl_arg_sign;
READLINE_DLL_IMPEXP int rl_visible_prompt_length;
READLINE_DLL_IMPEXP int rl_key_sequence_length;
READLINE_DLL_IMPEXP int rl_byte_oriented;

/* display.c */
READLINE_DLL_IMPEXP int rl_display_fixed;

/* parens.c */
READLINE_DLL_IMPEXP int rl_blink_matching_paren;

/*************************************************************************
 *									 *
 * Global functions and variables unsed and undocumented		 *
 *									 *
 *************************************************************************/

/* kill.c */
READLINE_DLL_IMPEXP int rl_set_retained_kills PARAMS((int));

/* terminal.c */
READLINE_DLL_IMPEXP void _rl_set_screen_size PARAMS((int, int));

/* undo.c */
READLINE_DLL_IMPEXP int _rl_fix_last_undo_of_type PARAMS((int, int, int));

/* util.c */
READLINE_DLL_IMPEXP char *_rl_savestring PARAMS((const char *));

/*************************************************************************
 *									 *
 * Functions and variables private to the readline library		 *
 *									 *
 *************************************************************************/

/* NOTE: Functions and variables prefixed with `_rl_' are
   pseudo-global: they are global so they can be shared
   between files in the readline library, but are not intended
   to be visible to readline callers. */

/*************************************************************************
 * Undocumented private functions					 *
 *************************************************************************/

#if defined(READLINE_CALLBACKS)

/* readline.c */
READLINE_DLL_IMPEXP void readline_internal_setup PARAMS((void));
READLINE_DLL_IMPEXP char *readline_internal_teardown PARAMS((int));
READLINE_DLL_IMPEXP int readline_internal_char PARAMS((void));

READLINE_DLL_IMPEXP _rl_keyseq_cxt *_rl_keyseq_cxt_alloc PARAMS((void));
READLINE_DLL_IMPEXP void _rl_keyseq_cxt_dispose PARAMS((_rl_keyseq_cxt *));
READLINE_DLL_IMPEXP void _rl_keyseq_chain_dispose PARAMS((void));

READLINE_DLL_IMPEXP int _rl_dispatch_callback PARAMS((_rl_keyseq_cxt *));
     
/* callback.c */
READLINE_DLL_IMPEXP _rl_callback_generic_arg *_rl_callback_data_alloc PARAMS((int));
READLINE_DLL_IMPEXP void _rl_callback_data_dispose PARAMS((_rl_callback_generic_arg *));

#endif /* READLINE_CALLBACKS */

/* bind.c */

/* complete.c */
READLINE_DLL_IMPEXP void _rl_reset_completion_state PARAMS((void));
READLINE_DLL_IMPEXP char _rl_find_completion_word PARAMS((int *, int *));
READLINE_DLL_IMPEXP void _rl_free_match_list PARAMS((char **));

/* display.c */
READLINE_DLL_IMPEXP char *_rl_strip_prompt PARAMS((char *));
READLINE_DLL_IMPEXP void _rl_move_cursor_relative PARAMS((int, const char *));
READLINE_DLL_IMPEXP void _rl_move_vert PARAMS((int));
READLINE_DLL_IMPEXP void _rl_save_prompt PARAMS((void));
READLINE_DLL_IMPEXP void _rl_restore_prompt PARAMS((void));
READLINE_DLL_IMPEXP char *_rl_make_prompt_for_search PARAMS((int));
READLINE_DLL_IMPEXP void _rl_erase_at_end_of_line PARAMS((int));
READLINE_DLL_IMPEXP void _rl_clear_to_eol PARAMS((int));
READLINE_DLL_IMPEXP void _rl_clear_screen PARAMS((void));
READLINE_DLL_IMPEXP void _rl_update_final PARAMS((void));
READLINE_DLL_IMPEXP void _rl_redisplay_after_sigwinch PARAMS((void));
READLINE_DLL_IMPEXP void _rl_clean_up_for_exit PARAMS((void));
READLINE_DLL_IMPEXP void _rl_erase_entire_line PARAMS((void));
READLINE_DLL_IMPEXP int _rl_current_display_line PARAMS((void));

/* input.c */
READLINE_DLL_IMPEXP int _rl_any_typein PARAMS((void));
READLINE_DLL_IMPEXP int _rl_input_available PARAMS((void));
READLINE_DLL_IMPEXP int _rl_input_queued PARAMS((int));
READLINE_DLL_IMPEXP void _rl_insert_typein PARAMS((int));
READLINE_DLL_IMPEXP int _rl_unget_char PARAMS((int));
READLINE_DLL_IMPEXP int _rl_pushed_input_available PARAMS((void));

/* isearch.c */
READLINE_DLL_IMPEXP _rl_search_cxt *_rl_scxt_alloc PARAMS((int, int));
READLINE_DLL_IMPEXP void _rl_scxt_dispose PARAMS((_rl_search_cxt *, int));

READLINE_DLL_IMPEXP int _rl_isearch_dispatch PARAMS((_rl_search_cxt *, int));
READLINE_DLL_IMPEXP int _rl_isearch_callback PARAMS((_rl_search_cxt *));

READLINE_DLL_IMPEXP int _rl_search_getchar PARAMS((_rl_search_cxt *));

/* macro.c */
READLINE_DLL_IMPEXP void _rl_with_macro_input PARAMS((char *));
READLINE_DLL_IMPEXP int _rl_next_macro_key PARAMS((void));
READLINE_DLL_IMPEXP void _rl_push_executing_macro PARAMS((void));
READLINE_DLL_IMPEXP void _rl_pop_executing_macro PARAMS((void));
READLINE_DLL_IMPEXP void _rl_add_macro_char PARAMS((int));
READLINE_DLL_IMPEXP void _rl_kill_kbd_macro PARAMS((void));

/* misc.c */
READLINE_DLL_IMPEXP int _rl_arg_overflow PARAMS((void));
READLINE_DLL_IMPEXP void _rl_arg_init PARAMS((void));
READLINE_DLL_IMPEXP int _rl_arg_getchar PARAMS((void));
READLINE_DLL_IMPEXP int _rl_arg_callback PARAMS((_rl_arg_cxt));
READLINE_DLL_IMPEXP void _rl_reset_argument PARAMS((void));

READLINE_DLL_IMPEXP void _rl_start_using_history PARAMS((void));
READLINE_DLL_IMPEXP int _rl_free_saved_history_line PARAMS((void));
READLINE_DLL_IMPEXP void _rl_set_insert_mode PARAMS((int, int));

READLINE_DLL_IMPEXP void _rl_revert_all_lines PARAMS((void));

/* nls.c */
READLINE_DLL_IMPEXP int _rl_init_eightbit PARAMS((void));

/* parens.c */
READLINE_DLL_IMPEXP void _rl_enable_paren_matching PARAMS((int));

/* readline.c */
READLINE_DLL_IMPEXP void _rl_init_line_state PARAMS((void));
READLINE_DLL_IMPEXP void _rl_set_the_line PARAMS((void));
READLINE_DLL_IMPEXP int _rl_dispatch PARAMS((int, Keymap));
READLINE_DLL_IMPEXP int _rl_dispatch_subseq PARAMS((int, Keymap, int));
READLINE_DLL_IMPEXP void _rl_internal_char_cleanup PARAMS((void));

/* rltty.c */
READLINE_DLL_IMPEXP int _rl_disable_tty_signals PARAMS((void));
READLINE_DLL_IMPEXP int _rl_restore_tty_signals PARAMS((void));
/* search.c */
READLINE_DLL_IMPEXP int _rl_nsearch_callback PARAMS((_rl_search_cxt *));

/* signals.c */
READLINE_DLL_IMPEXP void _rl_signal_handler PARAMS((int));

READLINE_DLL_IMPEXP void _rl_block_sigint PARAMS((void));
READLINE_DLL_IMPEXP void _rl_release_sigint PARAMS((void));
READLINE_DLL_IMPEXP void _rl_block_sigwinch PARAMS((void));
READLINE_DLL_IMPEXP void _rl_release_sigwinch PARAMS((void));

/* terminal.c */
READLINE_DLL_IMPEXP void _rl_get_screen_size PARAMS((int, int));
READLINE_DLL_IMPEXP int _rl_init_terminal_io PARAMS((const char *));
#ifdef _MINIX
READLINE_DLL_IMPEXP void _rl_output_character_function PARAMS((int));
#else
READLINE_DLL_IMPEXP int _rl_output_character_function PARAMS((int));
#endif
READLINE_DLL_IMPEXP void _rl_output_some_chars PARAMS((const char *, int));
READLINE_DLL_IMPEXP int _rl_backspace PARAMS((int));
READLINE_DLL_IMPEXP void _rl_enable_meta_key PARAMS((void));
READLINE_DLL_IMPEXP void _rl_control_keypad PARAMS((int));
READLINE_DLL_IMPEXP void _rl_set_cursor PARAMS((int, int));

/* text.c */
READLINE_DLL_IMPEXP void _rl_fix_point PARAMS((int));
READLINE_DLL_IMPEXP int _rl_replace_text PARAMS((const char *, int, int));
READLINE_DLL_IMPEXP int _rl_forward_char_internal PARAMS((int));
READLINE_DLL_IMPEXP int _rl_insert_char PARAMS((int, int));
READLINE_DLL_IMPEXP int _rl_overwrite_char PARAMS((int, int));
READLINE_DLL_IMPEXP int _rl_overwrite_rubout PARAMS((int, int));
READLINE_DLL_IMPEXP int _rl_rubout_char PARAMS((int, int));
#if defined (HANDLE_MULTIBYTE)
READLINE_DLL_IMPEXP int _rl_char_search_internal PARAMS((int, int, char *, int));
#else
READLINE_DLL_IMPEXP int _rl_char_search_internal PARAMS((int, int, int));
#endif
READLINE_DLL_IMPEXP int _rl_set_mark_at_pos PARAMS((int));

/* undo.c */
READLINE_DLL_IMPEXP UNDO_LIST *_rl_copy_undo_entry PARAMS((UNDO_LIST *));
READLINE_DLL_IMPEXP UNDO_LIST *_rl_copy_undo_list PARAMS((UNDO_LIST *));

/* util.c */
#if defined (USE_VARARGS) && defined (PREFER_STDARG)
READLINE_DLL_IMPEXP void _rl_ttymsg (const char *, ...)  __attribute__((__format__ (printf, 1, 2)));
READLINE_DLL_IMPEXP void _rl_errmsg (const char *, ...)  __attribute__((__format__ (printf, 1, 2)));
READLINE_DLL_IMPEXP void _rl_trace (const char *, ...)  __attribute__((__format__ (printf, 1, 2)));
#else
READLINE_DLL_IMPEXP void _rl_ttymsg ();
READLINE_DLL_IMPEXP void _rl_errmsg ();
READLINE_DLL_IMPEXP void _rl_trace ();
#endif

READLINE_DLL_IMPEXP int _rl_tropen PARAMS((void));

READLINE_DLL_IMPEXP int _rl_abort_internal PARAMS((void));
READLINE_DLL_IMPEXP int _rl_null_function PARAMS((int, int));
READLINE_DLL_IMPEXP char *_rl_strindex PARAMS((const char *, const char *));
READLINE_DLL_IMPEXP int _rl_qsort_string_compare PARAMS((char **, char **));
READLINE_DLL_IMPEXP int (_rl_uppercase_p) PARAMS((int));
READLINE_DLL_IMPEXP int (_rl_lowercase_p) PARAMS((int));
READLINE_DLL_IMPEXP int (_rl_pure_alphabetic) PARAMS((int));
READLINE_DLL_IMPEXP int (_rl_digit_p) PARAMS((int));
READLINE_DLL_IMPEXP int (_rl_to_lower) PARAMS((int));
READLINE_DLL_IMPEXP int (_rl_to_upper) PARAMS((int));
READLINE_DLL_IMPEXP int (_rl_digit_value) PARAMS((int));

/* vi_mode.c */
READLINE_DLL_IMPEXP void _rl_vi_initialize_line PARAMS((void));
READLINE_DLL_IMPEXP void _rl_vi_reset_last PARAMS((void));
READLINE_DLL_IMPEXP void _rl_vi_set_last PARAMS((int, int, int));
READLINE_DLL_IMPEXP int _rl_vi_textmod_command PARAMS((int));
READLINE_DLL_IMPEXP void _rl_vi_done_inserting PARAMS((void));
READLINE_DLL_IMPEXP int _rl_vi_domove_callback PARAMS((_rl_vimotion_cxt *));

/*************************************************************************
 * Undocumented private variables					 *
 *************************************************************************/

/* bind.c */
READLINE_DLL_IMPEXP const char * const _rl_possible_control_prefixes[3];
READLINE_DLL_IMPEXP const char * const _rl_possible_meta_prefixes[3];

/* callback.c */
READLINE_DLL_IMPEXP _rl_callback_func_t *_rl_callback_func;
READLINE_DLL_IMPEXP _rl_callback_generic_arg *_rl_callback_data;

/* complete.c */
READLINE_DLL_IMPEXP int _rl_complete_show_all;
READLINE_DLL_IMPEXP int _rl_complete_show_unmodified;
READLINE_DLL_IMPEXP int _rl_complete_mark_directories;
READLINE_DLL_IMPEXP int _rl_complete_mark_symlink_dirs;
READLINE_DLL_IMPEXP int _rl_completion_prefix_display_length;
READLINE_DLL_IMPEXP int _rl_completion_columns;
READLINE_DLL_IMPEXP int _rl_print_completions_horizontally;
READLINE_DLL_IMPEXP int _rl_completion_case_fold;
READLINE_DLL_IMPEXP int _rl_completion_case_map;
READLINE_DLL_IMPEXP int _rl_match_hidden_files;
READLINE_DLL_IMPEXP int _rl_page_completions;
READLINE_DLL_IMPEXP int _rl_skip_completed_text;
READLINE_DLL_IMPEXP int _rl_menu_complete_prefix_first;

/* display.c */
READLINE_DLL_IMPEXP int _rl_vis_botlin;
READLINE_DLL_IMPEXP int _rl_last_c_pos;
READLINE_DLL_IMPEXP int _rl_suppress_redisplay;
READLINE_DLL_IMPEXP int _rl_want_redisplay;

/* isearch.c */
READLINE_DLL_IMPEXP char *_rl_isearch_terminators;

READLINE_DLL_IMPEXP _rl_search_cxt *_rl_iscxt;

/* macro.c */
READLINE_DLL_IMPEXP char *_rl_executing_macro;

/* misc.c */
READLINE_DLL_IMPEXP int _rl_history_preserve_point;
READLINE_DLL_IMPEXP int _rl_history_saved_point;

READLINE_DLL_IMPEXP _rl_arg_cxt _rl_argcxt;

/* readline.c */
READLINE_DLL_IMPEXP int _rl_echoing_p;
READLINE_DLL_IMPEXP int _rl_horizontal_scroll_mode;
READLINE_DLL_IMPEXP int _rl_mark_modified_lines;
READLINE_DLL_IMPEXP int _rl_bell_preference;
READLINE_DLL_IMPEXP int _rl_meta_flag;
READLINE_DLL_IMPEXP int _rl_convert_meta_chars_to_ascii;
READLINE_DLL_IMPEXP int _rl_output_meta_chars;
READLINE_DLL_IMPEXP int _rl_bind_stty_chars;
READLINE_DLL_IMPEXP int _rl_revert_all_at_newline;
READLINE_DLL_IMPEXP int _rl_echo_control_chars;
READLINE_DLL_IMPEXP char *_rl_comment_begin;
READLINE_DLL_IMPEXP unsigned char _rl_parsing_conditionalized_out;
READLINE_DLL_IMPEXP Keymap _rl_keymap;
READLINE_DLL_IMPEXP FILE *_rl_in_stream;
READLINE_DLL_IMPEXP FILE *_rl_out_stream;
READLINE_DLL_IMPEXP int _rl_last_command_was_kill;
READLINE_DLL_IMPEXP int _rl_eof_char;
READLINE_DLL_IMPEXP procenv_t _rl_top_level;
READLINE_DLL_IMPEXP _rl_keyseq_cxt *_rl_kscxt;

/* search.c */
READLINE_DLL_IMPEXP _rl_search_cxt *_rl_nscxt;

/* signals.c */
READLINE_DLL_IMPEXP int _rl_interrupt_immediately;
READLINE_DLL_IMPEXP int volatile _rl_caught_signal;

READLINE_DLL_IMPEXP int _rl_echoctl;

READLINE_DLL_IMPEXP int _rl_intr_char;
READLINE_DLL_IMPEXP int _rl_quit_char;
READLINE_DLL_IMPEXP int _rl_susp_char;

/* terminal.c */
READLINE_DLL_IMPEXP int _rl_enable_keypad;
READLINE_DLL_IMPEXP int _rl_enable_meta;
READLINE_DLL_IMPEXP char *_rl_term_clreol;
READLINE_DLL_IMPEXP char *_rl_term_clrpag;
READLINE_DLL_IMPEXP char *_rl_term_im;
READLINE_DLL_IMPEXP char *_rl_term_ic;
READLINE_DLL_IMPEXP char *_rl_term_ei;
READLINE_DLL_IMPEXP char *_rl_term_DC;
READLINE_DLL_IMPEXP char *_rl_term_up;
READLINE_DLL_IMPEXP char *_rl_term_dc;
READLINE_DLL_IMPEXP char *_rl_term_cr;
READLINE_DLL_IMPEXP char *_rl_term_IC;
READLINE_DLL_IMPEXP char *_rl_term_forward_char;
READLINE_DLL_IMPEXP int _rl_screenheight;
READLINE_DLL_IMPEXP int _rl_screenwidth;
READLINE_DLL_IMPEXP int _rl_screenchars;
READLINE_DLL_IMPEXP int _rl_terminal_can_insert;
READLINE_DLL_IMPEXP int _rl_term_autowrap;

/* undo.c */
READLINE_DLL_IMPEXP int _rl_doing_an_undo;
READLINE_DLL_IMPEXP int _rl_undo_group_level;

/* vi_mode.c */
READLINE_DLL_IMPEXP int _rl_vi_last_command;
READLINE_DLL_IMPEXP _rl_vimotion_cxt *_rl_vimvcxt;

#endif /* _RL_PRIVATE_H_ */
