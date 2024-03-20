#ifndef LIBVSLOGGER_H_
#define LIBVSLOGGER_H_

#include <stdbool.h>
#include <stdio.h>

/* Available severity level for logging.
 * vslogger only log message with the same or lower level as the set config. */
enum vslogger_level {
  VSLOGGER_ERROR,
  VSLOGGER_WARN,
  VSLOGGER_INFO,
  VSLOGGER_DEBUG,
};

/* Config struct for vslogger */
struct vslogger_config {
  enum vslogger_level level; // maximum severity level to log
  FILE *destination; // log data destination (e.g. stdout, stderr, etc)
  bool enable_date; // enable date in log prefix (e.g. "[2024-03-20 21:28:55] example log")
  bool enable_prefix; // enable level in log prefix (e.g. "[INFO] example log")
};

/* Initialise vslogger with given config.
 * Subsequent call to this method will update the configuration. */
void vslogger_init(struct vslogger_config *params);

/* Freed up set configuration */
void vslogger_clear(void);

void vslogger_error(const char *msg);
void vslogger_errorf(const char *fmt, ...);
void vslogger_warn(const char *msg);
void vslogger_warnf(const char *fmt, ...);
void vslogger_info(const char *msg);
void vslogger_infof(const char *fmt, ...);
void vslogger_debug(const char *msg);
void vslogger_debugf(const char *fmt, ...);

#endif // LIBVSLOGGER_H_
