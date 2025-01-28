#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <valarray>
#include <random>
#include <iostream>
#include <fstream>

using namespace std;

const double xmin = -1.0, xmax = 1.0;
const double ymin = -1.0, ymax = 1.0;
const double kappa=0.5, sigma_t=100, sigma_s=100, v=sqrt(2), eps=0;

vector<double> produit_mat_vect(vector<double> U, int Nx, int Ny, double alpha , double beta, double gamma)
{
    
    double xmin, xmax, ymin, ymax,dx , dy ;
    
    double x, y;

    vector<double> Up(U.size());

   //calcul produit mat vecteur
    for (int i = 0; i < Nx*Ny; i++)
    {   
        
        x= xmin+ ((i %Nx)+1)*dx, y=ymin+((i/Nx) +1 )*dy ;
        if (i<Nx)
        {
            
            if (i %Nx==0)
            {   
            
                
                Up[i]=alpha*U[i]+beta*(U[i+1]+U[i+(Nx-1)])+gamma*(U[i+(Ny-1)*Nx]+U[i+Nx]);

            }
            else if (i%Nx==Nx-1)
            {
                Up[i]=alpha*U[i]+beta*(U[i-1]+U[i-(Nx-1)])+gamma*(U[i+(Ny-1)*Nx]+U[i+Nx]);
            
            }
            else
            {
                Up[i]=alpha*U[i]+beta*(U[i-1]+U[i+1])+gamma*(U[i+(Ny-1)*Nx]+U[i+Nx]);

            }
        }
        else if (i>=Nx*(Ny-1))
        {
            if (i %Nx==0)
            {
                Up[i]=alpha*U[i]+beta*(U[i+1]+U[i+(Nx-1)])+gamma*(U[i-Nx*(Ny-1)]+U[i-Nx]);

            }
            else if (i%Nx==Nx-1)
            {
                Up[i]=alpha*U[i]+beta*(U[i-1]+U[i-(Nx-1)])+gamma*(U[i-Nx*(Ny-1)]+U[i-Nx]);
            
            }
            else
            {
                Up[i]=alpha*U[i]+beta*(U[i-1]+U[i+1])+gamma*(U[i-Nx*(Ny-1)]+U[i-Nx]);

            }

        }
        else
        {   
            if (i %Nx==0)
            {
                Up[i]=alpha*U[i]+beta*(U[i+1]+U[i+(Nx-1)])+gamma*(U[i+Nx]+U[i-Nx]);

            }
            else if (i%Nx==Nx-1)
            {
                Up[i]=alpha*U[i]+beta*(U[i-1]+U[i-(Nx-1)])+gamma*(U[i+Nx]+U[i-Nx]);
            
            }
            else
            {
                Up[i]=alpha*U[i]+beta*(U[i-1]+U[i+1])+gamma*(U[i+Nx]+U[i-Nx]);

            }            
        }    
    }  
    return Up;
}

double norm(const vector<double>& v) 
{
    double norme=0;
    for (int i=0; i<=v.size(); i++)
    {
        norme+=v[i]*v[i];
    }
    norme=sqrt(norme);
    return norme;
}

double ps(vector<double> v1,vector<double> v2)
{
    double p=0;
    for (int i=0; i<=v1.size(); i++)
    {
        p+=v1[i]*v2[i];
    }
    return p;
}
vector<double> BiCg(vector<double>& b,int Nx,int Ny, double alpha,double beta, double gamma)
{
    int n = b.size();

    vector<double> x(n,0);
    vector<double> r(n), r_tilde(n), p(n), p_tilde(n);
    double rho0 = 0.0;
    x=produit_mat_vect(x,Nx,Ny,alpha,beta,gamma);
    // Calculer r = b - A * x
    for (int i = 0; i < n; i++)
    {
        
        r[i] = b[i] - x[i];
        r_tilde[i] = r[i];
        p[i] = r[i];
        rho0 += r[i] * r_tilde[i];
    }

    int k = 0,Nmax=1000;
    double epsilon=1e-6;
    double a, omega,rho, c;
    vector<double> h(n), s(n),t(n);

    for (int k=1; k <= Nmax;k++) {
        vector<double> nu(n);
        nu=p;
        // Calculer q = A * p
        nu=produit_mat_vect(nu,Nx,Ny,alpha,beta,gamma);

        

        a = rho0 / ps(r_tilde,nu);

        for (int i = 0; i < n; ++i) {
            h[i] =x[i]+ a * p[i];
            s[i] =r[i]- a * nu[i];
        }
        if (norm(s)<epsilon)
        {
            x=h;
            break;
        }
        t=s;
        t=produit_mat_vect(t,Nx,Ny,alpha,beta,gamma);
        omega=ps(t,s)/ps(t,t);
        for (int i = 0; i < n; ++i) {
            x[i]= h[i] +omega*s[i];
            r[i]=s[i]-omega*t[i];
        }

        if (norm(r)<epsilon)
        {
            break;
        }
        rho=ps(r_tilde,r);
        c = (rho / rho0)*(a/omega);

        for (int i = 0; i < n; ++i) {
            p[i] = r[i] + c * (p[i]-omega*nu[i]);
        }
        rho0 = rho;
        
        
    }

    return x;
}

// void create_directory(const std::string& dir_name) {
//     struct stat info;
//     if (stat(dir_name.c_str(), &info) != 0) {
//         // Créer le dossier
//         mkdir(dir_name.c_str(), 0777);
//     } else if (!(info.st_mode & S_IFDIR)) {
//         std::cerr << "Erreur : " << dir_name << " existe mais n'est pas un dossier." << std::endl;
//         exit(1);
//     }
// }

int main(int argc, char const *argv[]) {
    int Nx = 200, Ny = 200;
    double x, y, t, Tf, dt = 1e-1, dx, dy, alpha, beta, gamma;
    int i, j;
    Tf = 10 * dt;
    dx = (xmax - xmin) / Nx;
    dy = (ymax - ymin) / Ny;
    alpha = 1 + 2 * (v / (3 * sigma_s)) * dt * ((1. / (dx * dx)) + (1. / (dy * dy)) + v * sigma_t * gamma * eps);
    beta = -((v / (3 * sigma_s)) * dt) / (2 * dx * dx);
    gamma = -((v / (3 * sigma_s)) * dt) / (2 * dy * dy);

    printf("alpha=%lf, beta=%lf, gamma=%lf\n", alpha, beta, gamma);

    vector<double> U;
    U.resize(Nx * Ny);
    for (int k = 0; k < Nx * Ny; k++) {   
        i = (k % Nx) + 1;
        j = (k / Nx) + 1;
        x = xmin + i * dx;
        y = ymin + j * dy;
        U[k] = exp((-(x * x) / 0.0075) + (-(y * y) / 0.0075));
    }

    // Créer le dossier "reference" s'il n'existe pas
    // create_directory("reference");

    for (int n = 0; n <= floor(Tf / dt); n++) {
        t = n * dt;
        printf("boucle en temps n= %d, t=%lf\n", n, t);

        // Préfixer le nom du fichier avec "reference/"
        string name_file("reference/sol_ref_t" + to_string(n) + ".txt"); // Le nom de mon fichier
        ofstream fichier_sol;
        fichier_sol.open(name_file, ios::out);  // Ouvre un fichier appelé name_file

        for (int i = 0; i < (Nx) * (Ny); i++) {
            x = xmin + ((i % Nx) + 1) * dx;
            y = ymin + ((i / Nx) + 1) * dy;
            fichier_sol << x << " " << y << " " << U[i] << " " << endl;
        }
        fichier_sol.close();

        U = BiCg(U, Nx, Ny, alpha, beta, gamma);
    }

    return 0;
}


// int main(int argc, char const *argv[])
// {

//     int Nx=200, Ny=200;
//     double x,y,t,Tf,dt=1e-1,dx,dy, alpha, beta, gamma;
//     int i ,j;
//     Tf=10*dt;
//     dx=(xmax-xmin)/Nx;
//     dy=(ymax-ymin)/Ny;
//     alpha=1+2*(v/(3*sigma_s))*dt*((1./(dx*dx))+(1./(dy*dy))+v*sigma_t*gamma*eps);
//     beta=-((v/(3*sigma_s))*dt)/(2*dx*dx);
//     gamma=-((v/(3*sigma_s))*dt)/(2*dy*dy);

//     printf("alpha=%lf, beta=%lf, gamma=%lf\n", alpha,beta,gamma);



//     vector<double> U;
//     U.resize(Nx*Ny);
//     for (int k = 0; k < Nx*Ny; k++)
//     {   
//         i=(k %Nx)+1;
//         j=(k/Nx) +1;
//         x= xmin+ i*dx, y=ymin+j*dy ;
//         // printf("k=%d, U=%lf\n",k,U[k]);
//         // U[k]=k;
//         U[k]=exp((-(x * x) / 0.0075) + (-(y * y) / 0.0075));
        
//     }
     


//     for (int n=0; n<=floor(Tf/dt); n++)
//     {
//         t=n*dt;
//         printf("boucle en temps n= %d, t=%lf\n", n,t );
//         string name_file("sol_ref_t"+ to_string(n)+".txt"); // Le nom de mon fichier
//         ofstream fichier_sol;
//         fichier_sol.open(name_file, ios::out);  // Ouvre un fichier appelé name_file
       
//         for (int i = 0; i < (Nx)*(Ny) ; i++)
//         {
       
//             x=xmin+((i%Nx)+1)*dx;
//             y=ymin+((i/Nx)+1)*dy;            
//             fichier_sol << x << " " << y << " " << U[i] << " " << endl;
//         }
//         fichier_sol.close(); 
        
//         U=BiCg(U,Nx,Ny, alpha,beta,gamma);
    
              
//     }


//     return 0;
// }
