#pragma once

#include "type.h"

#ifdef __cplusplus
extern "C" {
#endif

struct EisSpectra
{
	void *priv;
};

bool eis_spectra_load_from_disk(struct EisSpectra* spectra, const char* path);
void eis_spectra_free(struct EisSpectra* spectra);
const char *eis_spectra_get_strerror(struct EisSpectra* spectra);

struct EisDataPoint *eis_spectra_get_datapoints(struct EisSpectra* spectra);
void eis_spectra_free_get_datapoints(struct EisSpectra *points);

const char *eis_spectra_get_model(struct EisSpectra *points);
const char *eis_spectra_get_header(struct EisSpectra *points);
const char *eis_spectra_get_header_description(struct EisSpectra *points);
double *eis_spectra_get_labels(struct EisSpectra *points);
const char **eis_spectra_get_label_names(struct EisSpectra *points);
void eis_spectra_free_label_names(char **names);

#ifdef __cplusplus
}
#endif
