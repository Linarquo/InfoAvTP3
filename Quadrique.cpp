#include "Quadrique.h"

using namespace Scene;

///////////////////////////////////////////////////////////////////////////////
///  public overloaded constructor  CQuadrique \n
///  Description : Constructeur par défaut
///
///  @return None
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CQuadrique::CQuadrique( void )
    : ISurface     (                  )
    , m_Quadratique( CVecteur3::ZERO  )
    , m_Lineaire   ( CVecteur3::ZERO  )
    , m_Mixte      ( CVecteur3::ZERO  )
    , m_Cst        ( RENDRE_REEL( 0 ) )
{}

///////////////////////////////////////////////////////////////////////////////
///  public overloaded constructor  CQuadrique \n
///  Description : Constructeur par défaut
///
///  @param [in]       Quadric const Scene::CQuadrique &   la quadrique à copier
///
///  @return None
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CQuadrique::CQuadrique( const CQuadrique& Quadric )
    : ISurface     ( Quadric               )
    , m_Quadratique( Quadric.m_Quadratique )
    , m_Lineaire   ( Quadric.m_Lineaire    )
    , m_Mixte      ( Quadric.m_Mixte       )
    , m_Cst        ( Quadric.m_Cst         )
{}

///////////////////////////////////////////////////////////////////////////////
///  public virtual destructor  ~CQuadrique \n
///  Description : Destructeur
///
///  @return None
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CQuadrique::~CQuadrique( void )
{
}

///////////////////////////////////////////////////////////////////////////////
///  public  operator = \n
///  Description : Opérateur de copie
///
///  @param [in]       Quadric const Scene::CQuadrique &    La quadrique à copier
///
///  @return Scene::CQuadrique & La quadrique modifiée
///
///  @author Olivier Dionne 
///  @date   14/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CQuadrique& CQuadrique::operator = ( const CQuadrique& Quadric )
{
    ISurface::operator =( Quadric );
    m_Quadratique = Quadric.m_Quadratique;
    m_Lineaire    = Quadric.m_Lineaire;
    m_Mixte       = Quadric.m_Mixte;
    m_Cst         = Quadric.m_Cst;
    return ( *this );
}

///////////////////////////////////////////////////////////////////////////////
///  protected virtual constant  AfficherInfoDebug \n
///  Description : Implémente le déboguage polymorphique par flux de sortie
///
///  @param [in, out]  Out std::ostream &    Le flux de sortie
///
///  @return std::ostream & Le flux de sortie modifié
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
ostream& CQuadrique::AfficherInfoDebug( ostream& Out ) const
{
    Out << "[DEBUG]: Quadric.Quadratique       = " << m_Quadratique << endl;
    Out << "[DEBUG]: Quadric.Lineaire          = " << m_Lineaire    << endl;
    Out << "[DEBUG]: Quadric.Mixte             = " << m_Mixte       << endl;
    Out << "[DEBUG]: Quadric.Constante         = " << m_Cst;
    return Out;
}

///////////////////////////////////////////////////////////////////////////////
///  public virtual  Pretraitement \n
///  Description : Pretraitement des données de la quadrique( appelé AVANT le lancer)
///
///  @return None
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
void CQuadrique::Pretraitement( void )
{
   // Algorithme tiré de ... 
   // R. Goldman, "Two Approach to a Computer Model for Quadric Surfaces",
   // IEEE CG&A, Sept 1983, pp.21
   
    REAL A = m_Quadratique.x;
	REAL B = m_Quadratique.y;
    REAL C = m_Quadratique.z;
    REAL D = m_Mixte.z    * RENDRE_REEL( 0.5 );
	REAL E = m_Mixte.x    * RENDRE_REEL( 0.5 );
	REAL F = m_Mixte.y    * RENDRE_REEL( 0.5 );
	REAL G = m_Lineaire.x * RENDRE_REEL( 0.5 );
	REAL H = m_Lineaire.y * RENDRE_REEL( 0.5 );
	REAL J = m_Lineaire.z * RENDRE_REEL( 0.5 );
	REAL K = m_Cst;

	CMatrice4 Q( A, D, F, G,
			     D, B, E, H,
			     F, E, C, J,
			     G, H, J, K );

    CMatrice4 Inverse = m_Transformation.Inverse();

    Q = Inverse * Q * Inverse.Transpose();

    m_Quadratique.x = Q[ 0 ][ 0 ];
    m_Quadratique.y = Q[ 1 ][ 1 ];
	m_Quadratique.z = Q[ 2 ][ 2 ];
	m_Cst           = Q[ 3 ][ 3 ];
	m_Mixte.x       = Q[ 1 ][ 2 ] * RENDRE_REEL( 2.0 );
	m_Mixte.y       = Q[ 0 ][ 2 ] * RENDRE_REEL( 2.0 );
	m_Mixte.z       = Q[ 0 ][ 1 ] * RENDRE_REEL( 2.0 );
	m_Lineaire.x    = Q[ 0 ][ 3 ] * RENDRE_REEL( 2.0 );
	m_Lineaire.y    = Q[ 1 ][ 3 ] * RENDRE_REEL( 2.0 );
    m_Lineaire.z    = Q[ 2 ][ 3 ] * RENDRE_REEL( 2.0 );
}

///////////////////////////////////////////////////////////////////////////////
///  public virtual  Intersection \n
///  Description : Effectue l'intersection Rayon/Quadrique
///
///  @param [in]       Rayon const CRayon &    Le rayon à tester
///
///  @return Scene::CIntersection Le résultat de l'ntersection
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CIntersection CQuadrique::Intersection( const CRayon& Rayon )
{
	CIntersection Result;

	// TODO: À COMPLÉTER ...

	// La référence pour l'algorithme d'intersection des quadriques est : 
	// Eric Haines, Paul Heckbert "An Introduction to Rayon Tracing",
	// Academic Press, Edited by Andrw S. Glassner, pp.68-73 & 288-293

	// S'il y a collision, ajuster les variables suivantes de la structure intersection :
	// Normale, Surface intersectée et la distance

	REAL A = m_Quadratique.x;
	REAL E = m_Quadratique.y;
	REAL H = m_Quadratique.z;
	REAL D = m_Lineaire.x;
	REAL G = m_Lineaire.y;
	REAL I = m_Lineaire.z;
	REAL B = m_Mixte.x;
	REAL C = m_Mixte.y;
	REAL F = m_Mixte.z;
	REAL J = m_Cst;

	CVecteur3 Rd = CVecteur3::Normaliser(Rayon.ObtenirDirection());

	REAL Xd = Rd.x;
	REAL Yd = Rd.y;
	REAL Zd = Rd.z;

	REAL X0 = Rayon.ObtenirOrigine().x;
	REAL Y0 = Rayon.ObtenirOrigine().y;
	REAL Z0 = Rayon.ObtenirOrigine().z;
	
	REAL Aq = Xd*(A*Xd + B*Yd + C*Zd) 
			+ Yd*(E*Yd + F*Zd) 
			+ H*Zd*Zd;
	REAL Bq = 2.f*(Xd*(A*X0+B/2.f*Y0+C/2.f*Z0+D/2.f)
			+ Yd*(B/2.f*X0+E*Y0+F/2.f*Z0+G/2.f)
			+ Zd*(C/2.f*X0+F/2.f*Y0+H*Z0+I/2.f));
	REAL Cq = X0*(A*X0+B*Y0+C*Z0+D)
			+ Y0*(E*Y0+F*Z0+G)
			+ Z0*(H*Z0+I)+J;

	REAL t =0;
	if (Aq != 0) {
		REAL delta = Bq*Bq - 4 * Aq*Cq;
		if (delta >= 0) {
			t = Min((-Bq + sqrt(delta)) / (2 * Aq), (-Bq - sqrt(delta)) / (2 * Aq));
		}
	}else {
		if (Bq!=0)
		{
			t = -Cq / Bq;
		}
	}

	if (t > 0) {
		CVecteur3 Pinters = CVecteur3(X0 + Xd*t, Y0 + Yd*t, Z0 + Zd*t);
		REAL xn =2.f*(A*Pinters.x + B/2.f*Pinters.y + C/2.f*Pinters.z + D/2.f);
		REAL yn =2.f*(B/2.f*Pinters.x + E*Pinters.y + F/2.f*Pinters.z + G/2.f);
		REAL zn =2.f*(C/2.f*Pinters.x + F/2.f*Pinters.y + H*Pinters.z + I/2.f);
		CVecteur3 normal = CVecteur3::Normaliser(CVecteur3(xn, yn, zn));
		if (CVecteur3::ProdScal(normal, Rayon.ObtenirDirection())>0)
		{
			normal = -normal;
		}
		Result.AjusterSurface(this);
		Result.AjusterNormale(normal);
		Result.AjusterDistance(CVecteur3::Distance(Pinters, Rayon.ObtenirOrigine()));
	}


	return Result;
}

///////////////////////////////////////////////////////////////////////////////
///  public virtual constant  Copier \n
///  Description : Alloue une copie de la quadrique courante
///
///  @return Scene::CQuadrique *la copie de la quadrique
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CQuadrique* CQuadrique::Copier( void ) const
{
    return new CQuadrique( *this );
}