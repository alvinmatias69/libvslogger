#include "config.h"

#include "libvslogger.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PREFIX_LENGTH 128
#define MAX_MSG_LENGTH 4096

#define PREFIX_ERROR "ERROR"
#define PREFIX_WARN "WARN"
#define PREFIX_INFO "INFO"
#define PREFIX_DEBUG "DEBUG"

struct vslogger_config *vslogger_instance = NULL;

void vslogger_print(const char *level_prefix, const char *msg,
                    enum vslogger_level level);
void vslogger_vprint(const char *level_prefix, const char *fmt, va_list args,
                     enum vslogger_level level);

void vslogger_init(struct vslogger_config *params) {
  if (vslogger_instance == NULL)
    vslogger_instance = reallocarray(NULL, 1, sizeof(struct vslogger_config));

  vslogger_instance->level = params->level;
  vslogger_instance->destination = params->destination;
  vslogger_instance->enable_prefix = params->enable_prefix;
  vslogger_instance->enable_date = params->enable_date;
}

void vslogger_clear(void) { free(vslogger_instance); }

void vslogger_error(const char *msg) {
  vslogger_print(PREFIX_ERROR, msg, VSLOGGER_ERROR);
}

void vslogger_errorf(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vslogger_vprint(PREFIX_ERROR, fmt, args, VSLOGGER_ERROR);
  va_end(args);
}

void vslogger_warn(const char *msg) {
  vslogger_print(PREFIX_WARN, msg, VSLOGGER_WARN);
}

void vslogger_warnf(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vslogger_vprint(PREFIX_WARN, fmt, args, VSLOGGER_WARN);
  va_end(args);
}

void vslogger_info(const char *msg) {
  vslogger_print(PREFIX_INFO, msg, VSLOGGER_INFO);
}

void vslogger_infof(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vslogger_vprint(PREFIX_INFO, fmt, args, VSLOGGER_INFO);
  va_end(args);
}

void vslogger_debug(const char *msg) {
  vslogger_print(PREFIX_DEBUG, msg, VSLOGGER_DEBUG);
}

void vslogger_debugf(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vslogger_vprint(PREFIX_DEBUG, fmt, args, VSLOGGER_DEBUG);
  va_end(args);
}

void vslogger_prepare_prefix(char *buffer, const char *level_prefix) {
  size_t position = 0;
  if (vslogger_instance->enable_prefix)
    position +=
        snprintf(buffer + position, MAX_PREFIX_LENGTH, "[%s]", level_prefix);

  if (vslogger_instance->enable_date) {
    struct tm *tm_info;
    time_t timer = time(NULL);
    tm_info = localtime(&timer);
    strftime(buffer + position, MAX_PREFIX_LENGTH, "[%Y-%m-%d %H:%M:%S]",
             tm_info);
  }
}

void vslogger_print(const char *level_prefix, const char *msg,
                    enum vslogger_level level) {
  if (level > vslogger_instance->level)
    return;

  char prefix[MAX_PREFIX_LENGTH];
  vslogger_prepare_prefix(prefix, level_prefix);

  if (strnlen(prefix, MAX_PREFIX_LENGTH) == 0) {
    fprintf(vslogger_instance->destination, "%s\n", msg);
    return;
  }

  fprintf(vslogger_instance->destination, "%s %s\n", prefix, msg);
}

void vslogger_vprint(const char *level_prefix, const char *fmt, va_list args,
                     enum vslogger_level level) {
  if (level > vslogger_instance->level)
    return;

  char prefix[MAX_PREFIX_LENGTH];
  vslogger_prepare_prefix(prefix, level_prefix);

  if (strnlen(prefix, MAX_PREFIX_LENGTH) == 0) {
    vfprintf(vslogger_instance->destination, fmt, args);
    return;
  }

  char msg[MAX_MSG_LENGTH];
  vsprintf(msg, fmt, args);
  fprintf(vslogger_instance->destination, "%s %s", prefix, msg);
}
