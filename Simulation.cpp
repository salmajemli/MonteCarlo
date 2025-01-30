#include "Simulation.hpp"
#include "parameters.hpp"



// Retourne les limites du domaine (xmin, xmax, ymin, ymax, etc.)
std::vector<std::vector<double>> AbstractDomain::get_DomainLimits() const{
   std::vector<std::vector<double>> DomainLimits(this->_simulationParams.Dim);
   DomainLimits[0] = {this->_simulationParams.xmin , this->_simulationParams.xmax};
   if (this->_simulationParams.Dim >= 2) {
      DomainLimits[1] = {this->_simulationParams.ymin , this->_simulationParams.ymax};
      if (this->_simulationParams.Dim == 3) {
         DomainLimits[2] = {this->_simulationParams.zmin , this->_simulationParams.zmax};
      }
   }

   return DomainLimits ; 
}


// Initialise une condition au départ pour les particules selon leur position et dimension
double AbstractDomain::initialCondition(const std::vector<double>& x, const std::vector<double>& v) const
{
    double u_0 = 0.0; 
    double rayon;

    switch (this->_simulationParams.Dim) {
        case 1:
            // if ( (x[0]>-1.0) && (x[0]<1.0)){
            //     u_0 = cos(2*3.14*x[0]);
            // }
            if ( (x[0]>-0.0) && (x[0]<0.7)){
                u_0 = 2.;
            }
            break;

        case 2:
            u_0 = exp((-(x[0] * x[0]) / 0.0075) + (-(x[1] * x[1]) / 0.0075));
            break;

        case 3:

            double r = sqrt((x[0])*(x[0]) + (x[1])*(x[1]) + (x[2])*(x[2]));

            if (r<0.5){
                 u_0 = 1.0;
            }
            else {
                u_0 = 0.0; // À l'extérieur de la sphère
            }

            break;

      
    }

    return u_0;
}


// Applique les conditions aux limites pour une particule lorsque celle-ci dépasse le domaine

void BoundaryDomain::applyBoundaryConditions(std::vector<double>& xp, double& sp, std::vector<double>& vp) const
{

   std::vector<std::vector<double>> DomainLimits= this->get_DomainLimits();
   for (int i = 0; i < this->_simulationParams.Dim; i++)
   {
      if (xp[i] <= DomainLimits[i][0])
      {
            xp[i] += (DomainLimits[i][1] - DomainLimits[i][0]);
            
      }
      else if (xp[i] >= DomainLimits[i][1] )
      {
            xp[i] -= (DomainLimits[i][1] - DomainLimits[i][0]);
         
      }
   }
    
};


// Calcule la norme d'un vecteur
double AbstractDomain::Norm_Vector(const std::vector<double> a, const std::vector<double> b) const {
        if (a.size() != b.size()) {
            throw std::invalid_argument(" Norm_Vector Vectors must be of the same size");
        }

        double result = 0.0;
        for (size_t i = 0; i < a.size(); ++i) {
            result += a[i] * b[i];
        }
        return std::sqrt(result);
    };


// Génère un vecteur vitesse aléatoire selon la dimension
std::vector<double> AbstractDomain::Vprime(const std::vector<double>& xp, const double& sp, const double& tau, const std::vector<double>& vp) const
{
    std::vector<double> vprime(this->_simulationParams.Dim); 
    std::random_device rd;
    std::default_random_engine generator(rd());

    switch (this->_simulationParams.Dim)
    {
        case 1:
            {
                std::uniform_real_distribution<double> uniform_real_distribution(-1.0, 1.0);
                double tirage = uniform_real_distribution(generator);
                vprime[0] = (tirage == 0.0) ? 0.0 : (tirage / std::abs(tirage));
            }
            break;

        case 2:
            {
                std::uniform_real_distribution<double> uniform_real_distribution(0.0, 2.0 * M_PI);
                double tirage = uniform_real_distribution(generator);
                vprime[0] =  std::cos(tirage);
                vprime[1] = std::sin(tirage);
            }
            break;

        case 3:
            {
                std::normal_distribution<double> normal_distribution(0.0, 1.0);
                for ( int i = 0 ; i<3 ; i++){
                  vprime[i] = normal_distribution(generator);
                }
                double Norm_vprime = this->Norm_Vector(vprime, vprime) ;
                for ( int i = 0 ; i<3 ; i++){
                  vprime[i] = vprime[i] / Norm_vprime;
                }
            }
            break;

        default:
            throw std::invalid_argument("Dimension number invalid");
    }

    return vprime;
}


    
std::vector<double> AbstractDomain::SumVec(const std::vector<double> a, const std::vector<double> b) const {
        std::vector<double> result(a.size());
        for (size_t i = 0; i < b.size(); ++i) {
            result[i]= a[i] + b[i];
        }
        return result;
    };


std::vector<double> AbstractDomain::dotProductScal(const double a, const std::vector<double> b) const {
        
        std::vector<double> result(b.size());
        for (size_t i = 0; i < b.size(); ++i) {
            result[i] = a * b[i];
        }
        return result;
    };


// Fonction pour calculer l'intégrale sur alpha pour une probabilité donnée
double AbstractDomain::integrateAlpha(double x,double s , std::vector<double> vp) const {
    int N = 100 ; // Pas d'intégration
    double step = s/N; 
    double integral = 0.0;
    
    // Intégration de sigma_t(x - v * alpha, t - alpha, v) sur [0, v]
    for (double alpha = 0.0; alpha <= s; alpha += step) {
        integral += vp[0] * this->_simulationParams.sigma_T * step; 
    }
    
    return integral;
}

// Simule τ suivant fτ(xp, sp, s, vp)ds
double AbstractDomain::sampleTau(const std::vector<double>& xp, const double& sp, const std::vector<double>& vp) const {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_real_distribution<double> distribution(0, 1);

    double sigma_t = this->_simulationParams.sigma_T;
    double v = 1.0 ;
    double Norm_v = this->Norm_Vector(vp, vp) ; // Norme du vecteur vp
    
    // Calcul de l'intégrale sur alpha
    double alpha_integral = integrateAlpha(xp[0],sp, vp); 

    // Calcul de l'exponentielle de l'intégrale
    double exp_term = exp(-alpha_integral);
    
    // Loi de probabilité simulée
    double factor = v * sigma_t;
   //  return -log(distribution(generator)) / (factor * exp_term) ;
    double epsilon = 1e-1 ; 
    if (sigma_t > 0) { return -log(distribution(generator)) / (sigma_t * Norm_v) ; }
    else {return sp + epsilon ;}
  

}



Particle::Particle(const AbstractDomain* Domain, const struct_simulationParams& simulationParams, const std::vector<double>& x) :
   _Domain(Domain),
   _simulationParams(simulationParams),
    _xp(x),
   _sp(simulationParams.time),
   _vp(simulationParams.velocity),
   _wp(1.0 / simulationParams.Nmc)
{
};



bool Particle::OutDomain() const
{

   std::vector<std::vector<double>> DomainLimits= this->_Domain ->get_DomainLimits();
   for (int i = 0; i < this->_simulationParams.Dim; ++i)
   {
      if (_xp[i] < DomainLimits[i][0] || _xp[i]  > DomainLimits[i][1])
      {
         return true;
      }
   }
   return false;
};


// Simule le mouvement d'une particule dans le domaine
void Particle::simulateMotion(double& vect_u)
{
//    std :: cout << _sp << std :: endl ;
   while ((this->_sp > 0) and (this->_wp > 0))
   {
      double tau = this->_Domain->sampleTau(this->_xp, this->_sp, this->_vp);
      if (tau > this->_sp)
      {
         this->_xp =  this->_Domain ->SumVec( this->_xp , this->_Domain ->dotProductScal(this->_sp, this->_vp) ) ;

         if (Particle::OutDomain())
         {
            this->_Domain->applyBoundaryConditions(this->_xp, this->_sp, this->_vp);
         }
         this->_sp = 0;
         vect_u += this->_wp * this->_Domain->initialCondition(this->_xp, this->_vp);

      }
      else
      {
         

         if (Particle::OutDomain())
         {
            this->_Domain->applyBoundaryConditions(this->_xp, tau, this->_vp);
         }

       
         this->_wp *= this->_simulationParams.sigma_S / this->_simulationParams.sigma_T;

         this->_vp = this->_Domain->Vprime(this->_xp, this->_sp, tau, this->_vp);


        
         this->_sp -= tau;
         this->_xp =  this->_Domain ->SumVec( this->_xp , this->_Domain ->dotProductScal(tau, this->_vp) ) ;

      }
   }
}


AbstractDomain::AbstractDomain(const struct_simulationParams& simulationParams) :
   _simulationParams(simulationParams)
{
};

AbstractDomain::~AbstractDomain()
{
};

BoundaryDomain::~BoundaryDomain()
{
};

Particle::~Particle()
{
};