#include "Triangle.h"

using namespace Scene;

///////////////////////////////////////////////////////////////////////////////
///  public overloaded constructor  CTriangle \n
///  Description : Constructeur par défaut
///
///  @return None
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CTriangle::CTriangle( void )
    : ISurface (                 )
    , m_Normale( CVecteur3::ZERO )
{}

///////////////////////////////////////////////////////////////////////////////
///  public overloaded constructor  CTriangle \n
///  Description : Constructeur par défaut
///
///  @param [in]       Triangle const Scene::CTriangle &    Le triangle à copier
///
///  @return None
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CTriangle::CTriangle( const CTriangle& Triangle )
    : ISurface ( Triangle           )
    , m_Normale( Triangle.m_Normale )
{
    for( int i = 0; i < 3; i++ )
        m_Pts[ i ] = Triangle.m_Pts[ i ];
}

///////////////////////////////////////////////////////////////////////////////
///  public virtual destructor  ~CTriangle \n
///  Description : Destructeur
///
///  @return None
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CTriangle::~CTriangle( void )
{
}

///////////////////////////////////////////////////////////////////////////////
///  public  operator = \n
///  Description : Opérateur de copie
///
///  @param [in]       Triangle const Scene::CTriangle &    Le triangle à copier
///
///  @return Scene::CTriangle & Le triangle modifié
///
///  @author Olivier Dionne 
///  @date   14/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CTriangle& CTriangle::operator = ( const CTriangle& Triangle )
{
    ISurface::operator =( Triangle );
    m_Normale = Triangle.m_Normale;

    for( int i = 0; i < 3; i++ )
        m_Pts[ i ] = Triangle.m_Pts[ i ];

    return ( *this );
}

///////////////////////////////////////////////////////////////////////////////
///  protected virtual constant  AfficherInfoDebug \n
///  Description : Implémente le déboguage polymorphique par flux de sortie
///
///  @param [in, out]  Out std::ostream &   Le flux de sortie
///
///  @return std::ostream & Le flux de sortie modifié
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
ostream& CTriangle::AfficherInfoDebug( ostream& Out ) const
{
    Out << "[DEBUG]: Triangle.Point1         = " << m_Pts[ 0 ] << endl;
    Out << "[DEBUG]: Triangle.Point2         = " << m_Pts[ 1 ] << endl;
    Out << "[DEBUG]: Triangle.Point3         = " << m_Pts[ 2 ] << endl;
    Out << "[DEBUG]: Triangle.Normale        = " << m_Normale;
    return Out;
}

///////////////////////////////////////////////////////////////////////////////
///  public virtual  Pretraitement \n
///  Description : Pretraitement des données du triangle ( Appelé AVANT le lancer)
///
///  @return None
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
void CTriangle::Pretraitement( void )
{
    for( int i = 0; i < 3; i++ )
        m_Pts[ i ] = m_Pts[ i ] * m_Transformation;
    CalculerNormale();
}

///////////////////////////////////////////////////////////////////////////////
///  public virtual  Intersection \n
///  Description : Effectue l'intersection Rayon/Triangle
///
///  @param [in]       Rayon const CRayon &    Le rayon à tester
///
///  @return Scene::CIntersection Le résultat de l'ntersection
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CIntersection CTriangle::Intersection( const CRayon& Rayon )
{
	CIntersection Result;

	// À COMPLÉTER ... 

	// Voici deux références pour acomplir le développement :
	// 1) Tomas Akenine-Moller and Eric Haines "Real-Time Rendering 2nd Ed." 2002, p.581
	// 2) Son article: http://www.graphics.cornell.edu/pubs/1997/MT97.pdf

	// Notez que la normale du triangle est déjà calculée lors du prétraitement
	// il suffit que de la passer à la structure d'intersection.

	/*CVecteur3 normal_T = m_Normale;
	CVecteur3 point_T = m_Pts[0];
	CVecteur3 origine_R = Rayon.ObtenirOrigine();
	CVecteur3 direction_R = Rayon.ObtenirDirection();
	
	REAL t;

	REAL dir_Scal_norm = CVecteur3::ProdScal(direction_R, normal_T);

	if (dir_Scal_norm != 0) {
		t = CVecteur3::ProdScal(point_T, normal_T) - CVecteur3::ProdScal(origine_R, normal_T);
		t = t / dir_Scal_norm;
		CVecteur3 points_Inter = origine_R + t * direction_R;

		CVecteur3 normal_P0 = CVecteur3::ProdVect(m_Pts[1] - m_Pts[2], normal_T);
		REAL prodScal0_Sommet0 = CVecteur3::ProdScal((m_Pts[0] - m_Pts[1]), normal_P0);
		REAL prodScal0_Inter = CVecteur3::ProdScal((points_Inter - m_Pts[1]), normal_P0);
		if (prodScal0_Sommet0*prodScal0_Inter >= 0) {
			
			CVecteur3 normal_P1 = CVecteur3::ProdVect(m_Pts[0] - m_Pts[2], normal_T);
			REAL prodScal1_Sommet1 = CVecteur3::ProdScal((m_Pts[1] - m_Pts[2]), normal_P1);
			REAL prodScal1_Inter = CVecteur3::ProdScal((points_Inter - m_Pts[2]), normal_P1);
			if (prodScal1_Sommet1*prodScal1_Inter >= 0) {

				CVecteur3 normal_P2 = CVecteur3::ProdVect(m_Pts[0] - m_Pts[1], normal_T);
				REAL prodScal2_Sommet2 = CVecteur3::ProdScal((m_Pts[2] - m_Pts[0]), normal_P2);
				REAL prodScal2_Inter = CVecteur3::ProdScal((points_Inter - m_Pts[0]), normal_P2);
				if (prodScal2_Sommet2*prodScal2_Inter >= 0) {
					Result.AjusterSurface(this);
					Result.AjusterNormale(normal_T);
					Result.AjusterDistance(CVecteur3::Distance(points_Inter, origine_R));
				}
			}
		}
	}*/

	//On recupère les valeurs qui nous seront utiles
	
	CVecteur3 V0 = m_Pts[0];
	CVecteur3 V1 = m_Pts[1];
	CVecteur3 V2 = m_Pts[2];
	

	CVecteur3 O = Rayon.ObtenirOrigine();
	CVecteur3 D = Rayon.ObtenirDirection();

	CVecteur3 E1 = V1 - V0;
	CVecteur3 E2 = V2 - V0;
	CVecteur3 T = O-V0;
	CVecteur3 P = CVecteur3::ProdVect(D, E2);
	CVecteur3 Q = CVecteur3::ProdVect(T, E1);
	REAL u;
	REAL v;
	REAL t;

	if (CVecteur3::ProdScal(P, E1) != 0) {
		u = 1 / CVecteur3::ProdScal(P, E1) * CVecteur3::ProdScal(P, T);
		v = 1 / CVecteur3::ProdScal(P, E1) * CVecteur3::ProdScal(Q, D);

		if (u >= 0 && v >= 0 && u + v <= 1) {
			t = 1 / CVecteur3::ProdScal(P, E1) * CVecteur3::ProdScal(Q, E2);
			CVecteur3 pointInters = O + t*D;
			Result.AjusterSurface(this);
			Result.AjusterNormale(m_Normale);
			Result.AjusterDistance(CVecteur3::Distance(pointInters, O));
		}
	}


    return Result;
}

///////////////////////////////////////////////////////////////////////////////
///  public virtual constant  Copier \n
///  Description : Alloue une copie du triangle courant
///
///  @return Scene::CTriangle * Nouvelle copie du triangle 
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
CTriangle* CTriangle::Copier( void ) const
{
    return new CTriangle( *this );
}

///////////////////////////////////////////////////////////////////////////////
///  private  CalculerNormale \n
///  Description : Calculer la normale du triangle à partir des côtés
///
///  @return None
///
///  @author Olivier Dionne 
///  @date   13/08/2008
///
///////////////////////////////////////////////////////////////////////////////
void CTriangle::CalculerNormale( void )
{
    CVecteur3 Edge1 = m_Pts[ 1 ] - m_Pts[ 0 ];
    CVecteur3 Edge2 = m_Pts[ 2 ] - m_Pts[ 0 ];
    m_Normale = CVecteur3::Normaliser( CVecteur3::ProdVect( Edge1, Edge2 ) );
}
