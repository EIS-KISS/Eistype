#include "c/spectra.h"
#include "c/type.h"
#include "spectra.h"
#include "type.h"
#include <cstring>

extern "C"
{

struct EisSpectraPriv
{
	eis::EisSpectra spectra;
	char *err;
};

bool eis_spectra_load_from_disk(struct EisSpectra* spectra, const char* path)
{
	struct EisSpectraPriv *priv = reinterpret_cast<struct EisSpectraPriv*>(calloc(0, sizeof(EisSpectraPriv)));
	spectra->priv = priv;
	try
	{
		priv->spectra = eis::EisSpectra::loadFromDisk(path);
		return true;
	}
	catch(const eis::file_error& err)
	{
		priv->err = strdup(err.what());
		return false;
	}
}

void eis_spectra_free(struct EisSpectra* spectra)
{
	struct EisSpectraPriv *priv = reinterpret_cast<struct EisSpectraPriv*>(spectra->priv);
	priv->spectra.~EisSpectra();
	if(priv->err)
		free(priv->err);
	free(priv);
}

const char *eis_spectra_get_strerror(struct EisSpectra* spectra)
{
	struct EisSpectraPriv *priv = reinterpret_cast<struct EisSpectraPriv*>(spectra->priv);
	return priv->err;
}

struct EisDataPoint *eis_spectra_get_datapoints(struct EisSpectra* spectra)
{
	struct EisSpectraPriv *priv = reinterpret_cast<struct EisSpectraPriv*>(spectra->priv);
	struct EisDataPoint *points = reinterpret_cast<struct EisDataPoint*>(malloc(sizeof(*points)*priv->spectra.data.size()));
	for(size_t i = 0; i < priv->spectra.data.size(); ++i)
		points[i].priv = &priv->spectra.data[i];
	return points;
}

void eis_spectra_free_get_datapoints(struct EisSpectra *points)
{
	free(points);
}

const char *eis_spectra_get_model(struct EisSpectra *spectra)
{
	struct EisSpectraPriv *priv = reinterpret_cast<struct EisSpectraPriv*>(spectra->priv);
	return priv->spectra.model.c_str();
}

const char *eis_spectra_get_header(struct EisSpectra *spectra)
{
	struct EisSpectraPriv *priv = reinterpret_cast<struct EisSpectraPriv*>(spectra->priv);
	return priv->spectra.header.c_str();
}

const char *eis_spectra_get_header_description(struct EisSpectra *spectra)
{
	struct EisSpectraPriv *priv = reinterpret_cast<struct EisSpectraPriv*>(spectra->priv);
	return priv->spectra.headerDescription.c_str();
}

double *eis_spectra_get_labels(struct EisSpectra *spectra)
{
	struct EisSpectraPriv *priv = reinterpret_cast<struct EisSpectraPriv*>(spectra->priv);
	return priv->spectra.labels.data();
}

const char **eis_spectra_get_label_names(struct EisSpectra *spectra)
{
	struct EisSpectraPriv *priv = reinterpret_cast<struct EisSpectraPriv*>(spectra->priv);
	const char **result = reinterpret_cast<const char**>(malloc(sizeof(*result)*priv->spectra.labelNames.size()));
	for(size_t i = 0; i < priv->spectra.labelNames.size(); ++i)
		*result = priv->spectra.labelNames[i].c_str();
	return result;
}

void eis_spectra_free_label_names(char **names)
{
	free(names);
}

}
