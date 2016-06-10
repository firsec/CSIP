
typedef struct csip_model CSIP_MODEL;
typedef int CSIP_RETCODE;
typedef int CSIP_STATUS;

/* return codes */
#define CSIP_RETCODE_OK 0
#define CSIP_RETCODE_FAIL 1

/* solver status */
#define CSIP_STATUS_OPTIMAL 0
#define CSIP_STATUS_INFEASIBLE 1
#define CSIP_STATUS_UNBOUNDED 2
#define CSIP_STATUS_INFORUNBD 3
#define CSIP_STATUS_NODELIMIT 4
#define CSIP_STATUS_TIMELIMIT 5
#define CSIP_STATUS_MEMLIMIT 6
#define CSIP_STATUS_USERLIMIT 7
#define CSIP_STATUS_UNKNOWN 8

CSIP_RETCODE CSIPcreateModel(CSIP_MODEL**);
CSIP_RETCODE CSIPfreeModel(CSIP_MODEL*);

/* variable types */
#define CSIP_VARTYPE_BINARY 1
#define CSIP_VARTYPE_INTEGER 2
#define CSIP_VARTYPE_IMPLINT 3
#define CSIP_VARTYPE_CONTINUOUS 4


CSIP_RETCODE CSIPaddVar(CSIP_MODEL*, double lowerbound, double upperbound, int vartype, int *idx);
CSIP_RETCODE CSIPchgVarLB(CSIP_MODEL*, int numindices, int *indices, double *lowerbounds);
CSIP_RETCODE CSIPchgVarUB(CSIP_MODEL*, int numindices, int *indices, double *upperbounds);

CSIP_RETCODE CSIPaddLinCons(CSIP_MODEL*, int numindices, int *indices, double *coefs, double lhs, double rhs, int *idx);

CSIP_RETCODE CSIPaddQuadCons(CSIP_MODEL*, int numlinindices, int *linindices,
                        double *lincoefs, int numquadterms,
                        int *quadrowindices, int *quadcolindices,
                        double *quadcoefs, double lhs, double rhs, int *idx);

CSIP_RETCODE CSIPaddSOS1(CSIP_MODEL*, int numindices, int *indices, double *weights, int *idx);

CSIP_RETCODE CSIPaddSOS2(CSIP_MODEL*, int numindices, int *indices, double *weights, int *idx);

CSIP_RETCODE CSIPsetObj(CSIP_MODEL*, int numindices, int *indices, double *coefs);

CSIP_RETCODE CSIPsolve(CSIP_MODEL*);

CSIP_RETCODE CSIPgetVarValues(CSIP_MODEL*, double *output);
double CSIPgetObjValue(CSIP_MODEL*);
CSIP_STATUS CSIPgetStatus(CSIP_MODEL*);

CSIP_RETCODE CSIPsetIntParam(CSIP_MODEL*, const char *name, int value);
CSIP_RETCODE CSIPsetDoubleParam(CSIP_MODEL*, const char *name, double value);
CSIP_RETCODE CSIPsetBoolParam(CSIP_MODEL*, const char *name, int value);
CSIP_RETCODE CSIPsetStringParam(CSIP_MODEL*, const char *name, const char *value);
CSIP_RETCODE CSIPsetLongIntParam(CSIP_MODEL*, const char *name, long long value);
CSIP_RETCODE CSIPsetCharParam(CSIP_MODEL*, const char *name, char value);

int CSIPgetNumVars(CSIP_MODEL*);

void *CSIPgetInternalSCIP(CSIP_MODEL*);

/* callback functions */
typedef struct SCIP_ConshdlrData CSIP_CBDATA;
CSIP_RETCODE CSIPcbGetVarValues(CSIP_CBDATA*, double *output);
CSIP_RETCODE CSIPcbAddLinCons(CSIP_CBDATA*, int numindices, int *indices, double *coefs, double lhs, double rhs, int islocal);

typedef CSIP_RETCODE (*CSIP_LAZYCALLBACK)(CSIP_MODEL*, CSIP_CBDATA*, void *userdata);

CSIP_RETCODE CSIPaddLazyCallback(CSIP_MODEL*, CSIP_LAZYCALLBACK, int fractional, void *userdata);
