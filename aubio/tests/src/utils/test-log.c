#include <aubio.h>
#include <stdio.h>
#include "aubio_priv.h"

const char_t *hdr = "CUSTOM HEADER: ";
const char_t *hdr2 = "OTHER HEADER: ";

/* an example of logging function that adds a custom header and prints
 * aubio debug messages on stdout instead of stderr */
void logging(int level, const char_t *message, void *data) {
  FILE *out;
  fprintf(stdout, "using custom logging function\n");
  if (level == AUBIO_LOG_ERR) {
    out = stderr;
  } else {
    out = stdout;
  }
  if ((level >= 0) && (data != NULL)) {
    fprintf(out, "%s", (const char_t *)data);
  }
  fprintf(out, "%s", message);
}

int main (void)
{
  fprintf(stdout, "### testing normal logging\n");
  AUBIO_ERR("testing normal AUBIO_LOG_ERR\n");
  AUBIO_WRN("testing normal AUBIO_LOG_WRN\n");
  AUBIO_MSG("testing normal AUBIO_LOG_MSG\n");
  AUBIO_DBG("testing normal AUBIO_LOG_DBG\n");

  fprintf(stdout, "### testing with one custom function\n");
  aubio_log_set_function(logging, (void *)hdr);
  AUBIO_ERR("testing recustom AUBIO_LOG_ERR\n");
  AUBIO_WRN("testing recustom AUBIO_LOG_WRN\n");
  AUBIO_MSG("testing recustom AUBIO_LOG_MSG\n");
  AUBIO_DBG("testing recustom AUBIO_LOG_DBG\n");

  fprintf(stdout, "### testing resetted logging\n");
  aubio_log_reset();
  AUBIO_ERR("testing uncustom AUBIO_LOG_ERR\n");
  AUBIO_WRN("testing uncustom AUBIO_LOG_WRN\n");
  AUBIO_MSG("testing uncustom AUBIO_LOG_MSG\n");
  AUBIO_DBG("testing uncustom AUBIO_LOG_DBG\n");

  fprintf(stdout, "### testing per level customization\n");
  aubio_log_set_level_function(AUBIO_LOG_ERR, logging, (void *)hdr2);
  aubio_log_set_level_function(AUBIO_LOG_WRN, logging, NULL);
  aubio_log_set_level_function(AUBIO_LOG_MSG, logging, (void *)hdr);
  AUBIO_ERR("testing custom AUBIO_LOG_ERR\n");
  AUBIO_WRN("testing custom AUBIO_LOG_WRN with data=NULL\n");
  AUBIO_MSG("testing custom AUBIO_LOG_MSG\n");
  AUBIO_DBG("testing uncustomized AUBIO_LOG_DBG\n");

  return 0;
}
