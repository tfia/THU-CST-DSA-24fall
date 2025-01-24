#ifndef _TEMPERATURE_H_

#ifdef __cplusplus
extern "C"
{
#endif

void init(int n, const int *x, const int *y, const int *t);

void query(int x1, int x2, int y1, int y2, int *tmin, int *tmax);

#ifdef __cplusplus
}
#endif

#endif //_TEMPERATURE_H_
