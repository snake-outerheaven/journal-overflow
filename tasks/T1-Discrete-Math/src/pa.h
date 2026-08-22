#ifndef PA_H
#define PA_H

#if defined(PA_BUILD_DLL)
#define PA_API __declspec (dllexport)
#elif defined(_WIN32)
#define PA_API __declspec (dllimport)
#else
#define PA_API
#endif

// função para calcular o enésimo termo de uma progressão aritmética.
PA_API int pa_termo (int a1, int n, int r);

PA_API int pa_soma (int a1, int an, int r);

// Interpola k termos inteiros entre dois termos de uma P.A.
PA_API int pa_interpolar (int primeiro, int ultimo, int k, int interpolados[]);

// Gera uma P.A. de ordem n a partir de n + 1 termos iniciais.
PA_API int pa_gerar_ordem (const int iniciais[], int ordem, int quantidade,
                           int resultado[]);

#endif
