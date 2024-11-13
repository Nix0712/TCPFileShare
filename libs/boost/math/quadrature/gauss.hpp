//  Copyright John Maddock 2015.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_QUADRATURE_GAUSS_HPP
#define BOOST_MATH_QUADRATURE_GAUSS_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <limits>
#include <vector>
#include <boost/math/special_functions/legendre.hpp>
#include <boost/math/constants/constants.hpp>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4127)
#endif

namespace boost { namespace math{ namespace quadrature{ namespace detail{

template <class T>
struct gauss_constant_category
{
   static const unsigned value =
      (std::numeric_limits<T>::is_specialized == 0) ? 999 :
      (std::numeric_limits<T>::radix == 2) ?
      (
#ifdef BOOST_HAS_FLOAT128
         (std::numeric_limits<T>::digits <= 113) && std::is_constructible<T, __float128>::value ? 0 :
#else
         (std::numeric_limits<T>::digits <= std::numeric_limits<long double>::digits) && std::is_constructible<T, long double>::value ? 0 :
#endif
         (std::numeric_limits<T>::digits10 <= 110) && std::is_constructible<T, const char*>::value ? 4 : 999
      ) : (std::numeric_limits<T>::digits10 <= 110) && std::is_constructible<T, const char*>::value ? 4 : 999;
   
   using storage_type =
      std::conditional_t<(std::numeric_limits<T>::is_specialized == 0), T,
         std::conditional_t<(std::numeric_limits<T>::radix == 2),
            std::conditional_t< ((std::numeric_limits<T>::digits <= std::numeric_limits<float>::digits) && std::is_constructible<T, float>::value),
               float,
               std::conditional_t<((std::numeric_limits<T>::digits <= std::numeric_limits<double>::digits) && std::is_constructible<T, double>::value),
                  double,
                  std::conditional_t<((std::numeric_limits<T>::digits <= std::numeric_limits<long double>::digits) && std::is_constructible<T, long double>::value),
                     long double,
#ifdef BOOST_HAS_FLOAT128
                     std::conditional_t<((std::numeric_limits<T>::digits <= 113) && std::is_constructible<T, __float128>::value),
                        __float128,
                        T
                     >
                  >
#else
                     T
                  >
#endif
               >
            >, T
         >
      >;
};

#ifndef BOOST_MATH_GAUSS_NO_COMPUTE_ON_DEMAND

template <class Real, unsigned N, unsigned Category>
class gauss_detail
{
   static std::vector<Real> calculate_weights()
   {
      std::vector<Real> result(abscissa().size(), 0);
      for (unsigned i = 0; i < abscissa().size(); ++i)
      {
         Real x = abscissa()[i];
         Real p = boost::math::legendre_p_prime(N, x);
         result[i] = 2 / ((1 - x * x) * p * p);
      }
      return result;
   }
public:
   static const std::vector<Real>& abscissa()
   {
      static std::vector<Real> data = boost::math::legendre_p_zeros<Real>(N);
      return data;
   }
   static const std::vector<Real>& weights()
   {
      static std::vector<Real> data = calculate_weights();
      return data;
   }
};

#else

template <class Real, unsigned N, unsigned Category>
class gauss_detail;

#endif
#ifndef BOOST_HAS_FLOAT128
template <class T>
class gauss_detail<T, 7, 0>
{
   using storage_type = typename gauss_constant_category<T>::storage_type;
public:
   static std::array<storage_type, 4> const & abscissa()
   {
      static constexpr std::array<storage_type, 4> data = {
         static_cast<storage_type>(0.00000000000000000000000000000000000e+00L),
         static_cast<storage_type>(4.05845151377397166906606412076961463e-01L),
         static_cast<storage_type>(7.41531185599394439863864773280788407e-01L),
         static_cast<storage_type>(9.49107912342758524526189684047851262e-01L),
      };
      return data;
   }
   static std::array<storage_type, 4> const & weights()
   {
      static constexpr std::array<storage_type, 4> data = {
         static_cast<storage_type>(4.17959183673469387755102040816326531e-01L),
         static_cast<storage_type>(3.81830050505118944950369775488975134e-01L),
         static_cast<storage_type>(2.79705391489276667901467771423779582e-01L),
         static_cast<storage_type>(1.29484966168869693270611432679082018e-01L),
      };
      return data;
   }
};
#else
template <class T>
class gauss_detail<T, 7, 0>
{
   using storage_type = typename gauss_constant_category<T>::storage_type;
public:
   static std::array<storage_type, 4> const & abscissa()
   {
      static const std::array<storage_type, 4> data = {
         static_cast<storage_type>(0.00000000000000000000000000000000000e+00Q),
         static_cast<storage_type>(4.05845151377397166906606412076961463e-01Q),
         static_cast<storage_type>(7.41531185599394439863864773280788407e-01Q),
         static_cast<storage_type>(9.49107912342758524526189684047851262e-01Q),
      };
      return data;
   }
   static std::array<storage_type, 4> const & weights()
   {
      static const std::array<storage_type, 4> data = {
         static_cast<storage_type>(4.17959183673469387755102040816326531e-01Q),
         static_cast<storage_type>(3.81830050505118944950369775488975134e-01Q),
         static_cast<storage_type>(2.79705391489276667901467771423779582e-01Q),
         static_cast<storage_type>(1.29484966168869693270611432679082018e-01Q),
      };
      return data;
   }
};
#endif
template <class T>
class gauss_detail<T, 7, 4>
{
public:
   static  std::array<T, 4> const & abscissa()
   {
      static  std::array<T, 4> data = { // LCOV_EXCL_START
         BOOST_MATH_HUGE_CONSTANT(T, 0, 0.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000e+00),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 4.0584515137739716690660641207696146334738201409937012638704325179466381322612565532831268972774658776528675866604802e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 7.4153118559939443986386477328078840707414764714139026011995535196742987467218051379282683236686324705969251809311201e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 9.4910791234275852452618968404785126240077093767061778354876910391306333035484014080573077002792572414430073966699522e-01),
      }; // LCOV_EXCL_STOP
      return data;
   }
   static  std::array<T, 4> const & weights()
   {
      static  std::array<T, 4> data = { // LCOV_EXCL_START
         BOOST_MATH_HUGE_CONSTANT(T, 0, 4.1795918367346938775510204081632653061224489795918367346938775510204081632653061224489795918367346938775510204081633e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 3.8183005050511894495036977548897513387836508353386273475108345103070554643412970834868465934404480145031467176458536e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 2.7970539148927666790146777142377958248692506522659876453701403269361881043056267681324094290119761876632337521337205e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 1.2948496616886969327061143267908201832858740225994666397720863872465523497204230871562541816292084508948440200163443e-01),
      }; // LCOV_EXCL_STOP
      return data;
   }
};
#ifndef BOOST_HAS_FLOAT128
template <class T>
class gauss_detail<T, 10, 0>
{
   using storage_type = typename gauss_constant_category<T>::storage_type;
public:
   static std::array<storage_type, 5> const & abscissa()
   {
      static constexpr std::array<storage_type, 5> data = {
         static_cast<storage_type>(1.48874338981631210884826001129719985e-01L),
         static_cast<storage_type>(4.33395394129247190799265943165784162e-01L),
         static_cast<storage_type>(6.79409568299024406234327365114873576e-01L),
         static_cast<storage_type>(8.65063366688984510732096688423493049e-01L),
         static_cast<storage_type>(9.73906528517171720077964012084452053e-01L),
      };
      return data;
   }
   static std::array<storage_type, 5> const & weights()
   {
      static constexpr std::array<storage_type, 5> data = {
         static_cast<storage_type>(2.95524224714752870173892994651338329e-01L),
         static_cast<storage_type>(2.69266719309996355091226921569469353e-01L),
         static_cast<storage_type>(2.19086362515982043995534934228163192e-01L),
         static_cast<storage_type>(1.49451349150580593145776339657697332e-01L),
         static_cast<storage_type>(6.66713443086881375935688098933317929e-02L),
      };
      return data;
   }
};
#else
template <class T>
class gauss_detail<T, 10, 0>
{
   using storage_type = typename gauss_constant_category<T>::storage_type;
public:
   static std::array<storage_type, 5> const & abscissa()
   {
      static const std::array<storage_type, 5> data = {
         static_cast<storage_type>(1.48874338981631210884826001129719985e-01Q),
         static_cast<storage_type>(4.33395394129247190799265943165784162e-01Q),
         static_cast<storage_type>(6.79409568299024406234327365114873576e-01Q),
         static_cast<storage_type>(8.65063366688984510732096688423493049e-01Q),
         static_cast<storage_type>(9.73906528517171720077964012084452053e-01Q),
      };
      return data;
   }
   static std::array<storage_type, 5> const & weights()
   {
      static const std::array<storage_type, 5> data = {
         static_cast<storage_type>(2.95524224714752870173892994651338329e-01Q),
         static_cast<storage_type>(2.69266719309996355091226921569469353e-01Q),
         static_cast<storage_type>(2.19086362515982043995534934228163192e-01Q),
         static_cast<storage_type>(1.49451349150580593145776339657697332e-01Q),
         static_cast<storage_type>(6.66713443086881375935688098933317929e-02Q),
      };
      return data;
   }
};
#endif
template <class T>
class gauss_detail<T, 10, 4>
{
public:
   static  std::array<T, 5> const & abscissa()
   {
      static  std::array<T, 5> data = { // LCOV_EXCL_START
         BOOST_MATH_HUGE_CONSTANT(T, 0, 1.4887433898163121088482600112971998461756485942069169570798925351590361735566852137117762979946369123003116080525534e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 4.3339539412924719079926594316578416220007183765624649650270151314376698907770350122510275795011772122368293504099894e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 6.7940956829902440623432736511487357576929471183480946766481718895255857539507492461507857357048037949983390204739932e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 8.6506336668898451073209668842349304852754301496533045252195973184537475513805556135679072894604577069440463108641177e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 9.7390652851717172007796401208445205342826994669238211923121206669659520323463615962572356495626855625823304251877421e-01),
      }; // LCOV_EXCL_STOP
      return data;
   }
   static  std::array<T, 5> const & weights()
   {
      static  std::array<T, 5> data = { // LCOV_EXCL_START
         BOOST_MATH_HUGE_CONSTANT(T, 0, 2.9552422471475287017389299465133832942104671702685360135430802975599593821715232927035659579375421672271716440125256e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 2.6926671930999635509122692156946935285975993846088379580056327624215343231917927676422663670925276075559581145036870e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 2.1908636251598204399553493422816319245877187052267708988095654363519991065295128124268399317720219278659121687281289e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 1.4945134915058059314577633965769733240255663966942736783547726875323865472663001094594726463473195191400575256104544e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 6.6671344308688137593568809893331792857864834320158145128694881613412064084087101776785509685058877821090054714520419e-02),
      }; // LCOV_EXCL_STOP
      return data;
   }
};

#ifndef BOOST_HAS_FLOAT128
template <class T>
class gauss_detail<T, 15, 0>
{
   using storage_type = typename gauss_constant_category<T>::storage_type;
public:
   static std::array<storage_type, 8> const & abscissa()
   {
      static constexpr std::array<storage_type, 8> data = {
         static_cast<storage_type>(0.00000000000000000000000000000000000e+00L),
         static_cast<storage_type>(2.01194093997434522300628303394596208e-01L),
         static_cast<storage_type>(3.94151347077563369897207370981045468e-01L),
         static_cast<storage_type>(5.70972172608538847537226737253910641e-01L),
         static_cast<storage_type>(7.24417731360170047416186054613938010e-01L),
         static_cast<storage_type>(8.48206583410427216200648320774216851e-01L),
         static_cast<storage_type>(9.37273392400705904307758947710209471e-01L),
         static_cast<storage_type>(9.87992518020485428489565718586612581e-01L),
      };
      return data;
   }
   static std::array<storage_type, 8> const & weights()
   {
      static constexpr std::array<storage_type, 8> data = {
         static_cast<storage_type>(2.02578241925561272880620199967519315e-01L),
         static_cast<storage_type>(1.98431485327111576456118326443839325e-01L),
         static_cast<storage_type>(1.86161000015562211026800561866422825e-01L),
         static_cast<storage_type>(1.66269205816993933553200860481208811e-01L),
         static_cast<storage_type>(1.39570677926154314447804794511028323e-01L),
         static_cast<storage_type>(1.07159220467171935011869546685869303e-01L),
         static_cast<storage_type>(7.03660474881081247092674164506673385e-02L),
         static_cast<storage_type>(3.07532419961172683546283935772044177e-02L),
      };
      return data;
   }
};
#else
template <class T>
class gauss_detail<T, 15, 0>
{
   using storage_type = typename gauss_constant_category<T>::storage_type;
public:
   static std::array<storage_type, 8> const & abscissa()
   {
      static const std::array<storage_type, 8> data = {
         static_cast<storage_type>(0.00000000000000000000000000000000000e+00Q),
         static_cast<storage_type>(2.01194093997434522300628303394596208e-01Q),
         static_cast<storage_type>(3.94151347077563369897207370981045468e-01Q),
         static_cast<storage_type>(5.70972172608538847537226737253910641e-01Q),
         static_cast<storage_type>(7.24417731360170047416186054613938010e-01Q),
         static_cast<storage_type>(8.48206583410427216200648320774216851e-01Q),
         static_cast<storage_type>(9.37273392400705904307758947710209471e-01Q),
         static_cast<storage_type>(9.87992518020485428489565718586612581e-01Q),
      };
      return data;
   }
   static std::array<storage_type, 8> const & weights()
   {
      static const std::array<storage_type, 8> data = {
         static_cast<storage_type>(2.02578241925561272880620199967519315e-01Q),
         static_cast<storage_type>(1.98431485327111576456118326443839325e-01Q),
         static_cast<storage_type>(1.86161000015562211026800561866422825e-01Q),
         static_cast<storage_type>(1.66269205816993933553200860481208811e-01Q),
         static_cast<storage_type>(1.39570677926154314447804794511028323e-01Q),
         static_cast<storage_type>(1.07159220467171935011869546685869303e-01Q),
         static_cast<storage_type>(7.03660474881081247092674164506673385e-02Q),
         static_cast<storage_type>(3.07532419961172683546283935772044177e-02Q),
      };
      return data;
   }
};
#endif
template <class T>
class gauss_detail<T, 15, 4>
{
public:
   static  std::array<T, 8> const & abscissa()
   {
      static  std::array<T, 8> data = { // LCOV_EXCL_START
         BOOST_MATH_HUGE_CONSTANT(T, 0, 0.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000e+00),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 2.0119409399743452230062830339459620781283645446263767961594972460994823900302018760183625806752105908967902257386509e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 3.9415134707756336989720737098104546836275277615869825503116534395160895778696141797549711416165976202589352169635648e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 5.7097217260853884753722673725391064123838639628274960485326541705419537986975857948341462856982614477912646497026257e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 7.2441773136017004741618605461393800963089929458410256355142342070412378167792521899610109760313432626923598549381925e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 8.4820658341042721620064832077421685136625617473699263409572755876067507517414548519760771975082148085090373835713340e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 9.3727339240070590430775894771020947124399627351530445790136307635020297379704552795054758617426808659746824044603157e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 9.8799251802048542848956571858661258114697281712376148999999751558738843736901942471272205036831914497667516843990079e-01),
      }; // LCOV_EXCL_STOP
      return data;
   }
   static  std::array<T, 8> const & weights()
   {
      static  std::array<T, 8> data = { // LCOV_EXCL_START
         BOOST_MATH_HUGE_CONSTANT(T, 0, 2.0257824192556127288062019996751931483866215800947735679670411605143539875474607409339344071278803213535148267082999e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 1.9843148532711157645611832644383932481869255995754199348473792792912479753343426813331499916481782320766020854889310e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 1.8616100001556221102680056186642282450622601227792840281549572731001325550269916061894976888609932360539977709001384e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 1.6626920581699393355320086048120881113090018009841290732186519056355356321227851771070517429241553621484461540657185e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 1.3957067792615431444780479451102832252085027531551124320239112863108844454190781168076825736357133363814908889327664e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 1.0715922046717193501186954668586930341554371575810198068702238912187799485231579972568585713760862404439808767837506e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 7.0366047488108124709267416450667338466708032754330719825907292914387055512874237044840452066693939219355489858595041e-02),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 3.0753241996117268354628393577204417721748144833434074264228285504237189467117168039038770732399404002516991188859473e-02),
      }; // LCOV_EXCL_STOP
      return data;
   }
};

#ifndef BOOST_HAS_FLOAT128
template <class T>
class gauss_detail<T, 20, 0>
{
   using storage_type = typename gauss_constant_category<T>::storage_type;
public:
   static std::array<storage_type, 10> const & abscissa()
   {
      static constexpr std::array<storage_type, 10> data = {
         static_cast<storage_type>(7.65265211334973337546404093988382110e-02L),
         static_cast<storage_type>(2.27785851141645078080496195368574625e-01L),
         static_cast<storage_type>(3.73706088715419560672548177024927237e-01L),
         static_cast<storage_type>(5.10867001950827098004364050955250998e-01L),
         static_cast<storage_type>(6.36053680726515025452836696226285937e-01L),
         static_cast<storage_type>(7.46331906460150792614305070355641590e-01L),
         static_cast<storage_type>(8.39116971822218823394529061701520685e-01L),
         static_cast<storage_type>(9.12234428251325905867752441203298113e-01L),
         static_cast<storage_type>(9.63971927277913791267666131197277222e-01L),
         static_cast<storage_type>(9.93128599185094924786122388471320278e-01L),
      };
      return data;
   }
   static std::array<storage_type, 10> const & weights()
   {
      static constexpr std::array<storage_type, 10> data = {
         static_cast<storage_type>(1.52753387130725850698084331955097593e-01L),
         static_cast<storage_type>(1.49172986472603746787828737001969437e-01L),
         static_cast<storage_type>(1.42096109318382051329298325067164933e-01L),
         static_cast<storage_type>(1.31688638449176626898494499748163135e-01L),
         static_cast<storage_type>(1.18194531961518417312377377711382287e-01L),
         static_cast<storage_type>(1.01930119817240435036750135480349876e-01L),
         static_cast<storage_type>(8.32767415767047487247581432220462061e-02L),
         static_cast<storage_type>(6.26720483341090635695065351870416064e-02L),
         static_cast<storage_type>(4.06014298003869413310399522749321099e-02L),
         static_cast<storage_type>(1.76140071391521183118619623518528164e-02L),
      };
      return data;
   }
};
#else
template <class T>
class gauss_detail<T, 20, 0>
{
   using storage_type = typename gauss_constant_category<T>::storage_type;
public:
   static std::array<storage_type, 10> const & abscissa()
   {
      static const std::array<storage_type, 10> data = {
         static_cast<storage_type>(7.65265211334973337546404093988382110e-02Q),
         static_cast<storage_type>(2.27785851141645078080496195368574625e-01Q),
         static_cast<storage_type>(3.73706088715419560672548177024927237e-01Q),
         static_cast<storage_type>(5.10867001950827098004364050955250998e-01Q),
         static_cast<storage_type>(6.36053680726515025452836696226285937e-01Q),
         static_cast<storage_type>(7.46331906460150792614305070355641590e-01Q),
         static_cast<storage_type>(8.39116971822218823394529061701520685e-01Q),
         static_cast<storage_type>(9.12234428251325905867752441203298113e-01Q),
         static_cast<storage_type>(9.63971927277913791267666131197277222e-01Q),
         static_cast<storage_type>(9.93128599185094924786122388471320278e-01Q),
      };
      return data;
   }
   static std::array<storage_type, 10> const & weights()
   {
      static const std::array<storage_type, 10> data = {
         static_cast<storage_type>(1.52753387130725850698084331955097593e-01Q),
         static_cast<storage_type>(1.49172986472603746787828737001969437e-01Q),
         static_cast<storage_type>(1.42096109318382051329298325067164933e-01Q),
         static_cast<storage_type>(1.31688638449176626898494499748163135e-01Q),
         static_cast<storage_type>(1.18194531961518417312377377711382287e-01Q),
         static_cast<storage_type>(1.01930119817240435036750135480349876e-01Q),
         static_cast<storage_type>(8.32767415767047487247581432220462061e-02Q),
         static_cast<storage_type>(6.26720483341090635695065351870416064e-02Q),
         static_cast<storage_type>(4.06014298003869413310399522749321099e-02Q),
         static_cast<storage_type>(1.76140071391521183118619623518528164e-02Q),
      };
      return data;
   }
};
#endif
template <class T>
class gauss_detail<T, 20, 4>
{
public:
   static  std::array<T, 10> const & abscissa()
   {
      static  std::array<T, 10> data = { // LCOV_EXCL_START
         BOOST_MATH_HUGE_CONSTANT(T, 0, 7.6526521133497333754640409398838211004796266813497500804795244384256342048336978241545114181556215606998505646364133e-02),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 2.2778585114164507808049619536857462474308893768292747231463573920717134186355582779495212519096870803177373131560430e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 3.7370608871541956067254817702492723739574632170568271182794861351564576437305952789589568363453337894476772208852815e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 5.1086700195082709800436405095525099842549132920242683347234861989473497039076572814403168305086777919832943068843526e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 6.3605368072651502545283669622628593674338911679936846393944662254654126258543013255870319549576130658211710937772596e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 7.4633190646015079261430507035564159031073067956917644413954590606853535503815506468110411362064752061238490065167656e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 8.3911697182221882339452906170152068532962936506563737325249272553286109399932480991922934056595764922060422035306914e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 9.1223442825132590586775244120329811304918479742369177479588221915807089120871907893644472619292138737876039175464603e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 9.6397192727791379126766613119727722191206032780618885606353759389204158078438305698001812525596471563131043491596423e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 9.9312859918509492478612238847132027822264713090165589614818413121798471762775378083944940249657220927472894034724419e-01),
      }; // LCOV_EXCL_STOP
      return data;
   }
   static  std::array<T, 10> const & weights()
   {
      static  std::array<T, 10> data = { // LCOV_EXCL_START
         BOOST_MATH_HUGE_CONSTANT(T, 0, 1.5275338713072585069808433195509759349194864511237859727470104981759745316273778153557248783650390593544001842813788e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 1.4917298647260374678782873700196943669267990408136831649621121780984442259558678069396132603521048105170913854567338e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 1.4209610931838205132929832506716493303451541339202030333736708298382808749793436761694922428320058260133068573666201e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 1.3168863844917662689849449974816313491611051114698352699643649370885435642948093314355797518397262924510598005463625e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 1.1819453196151841731237737771138228700504121954896877544688995202017474835051151630572868782581901744606267543092317e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 1.0193011981724043503675013548034987616669165602339255626197161619685232202539434647534931576947985821375859035525483e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 8.3276741576704748724758143222046206100177828583163290744882060785693082894079419471375190843790839349096116111932764e-02),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 6.2672048334109063569506535187041606351601076578436364099584345437974811033665678644563766056832203512603253399592073e-02),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 4.0601429800386941331039952274932109879090639989951536817606854561832296750987328295538920623044384976189825709675075e-02),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 1.7614007139152118311861962351852816362143105543336732524349326677348419259621847817403105542146097668703716227512570e-02),
      }; // LCOV_EXCL_STOP
      return data;
   }
};

#ifndef BOOST_HAS_FLOAT128
template <class T>
class gauss_detail<T, 25, 0>
{
   using storage_type = typename gauss_constant_category<T>::storage_type;
public:
   static std::array<storage_type, 13> const & abscissa()
   {
      static constexpr std::array<storage_type, 13> data = {
         static_cast<storage_type>(0.00000000000000000000000000000000000e+00L),
         static_cast<storage_type>(1.22864692610710396387359818808036806e-01L),
         static_cast<storage_type>(2.43866883720988432045190362797451586e-01L),
         static_cast<storage_type>(3.61172305809387837735821730127640667e-01L),
         static_cast<storage_type>(4.73002731445714960522182115009192041e-01L),
         static_cast<storage_type>(5.77662930241222967723689841612654067e-01L),
         static_cast<storage_type>(6.73566368473468364485120633247622176e-01L),
         static_cast<storage_type>(7.59259263037357630577282865204360976e-01L),
         static_cast<storage_type>(8.33442628760834001421021108693569569e-01L),
         static_cast<storage_type>(8.94991997878275368851042006782804954e-01L),
         static_cast<storage_type>(9.42974571228974339414011169658470532e-01L),
         static_cast<storage_type>(9.76663921459517511498315386479594068e-01L),
         static_cast<storage_type>(9.95556969790498097908784946893901617e-01L),
      };
      return data;
   }
   static std::array<storage_type, 13> const & weights()
   {
      static constexpr std::array<storage_type, 13> data = {
         static_cast<storage_type>(1.23176053726715451203902873079050142e-01L),
         static_cast<storage_type>(1.22242442990310041688959518945851506e-01L),
         static_cast<storage_type>(1.19455763535784772228178126512901047e-01L),
         static_cast<storage_type>(1.14858259145711648339325545869555809e-01L),
         static_cast<storage_type>(1.08519624474263653116093957050116619e-01L),
         static_cast<storage_type>(1.00535949067050644202206890392685827e-01L),
         static_cast<storage_type>(9.10282619829636498114972207028916534e-02L),
         static_cast<storage_type>(8.01407003350010180132349596691113023e-02L),
         static_cast<storage_type>(6.80383338123569172071871856567079686e-02L),
         static_cast<storage_type>(5.49046959758351919259368915404733242e-02L),
         static_cast<storage_type>(4.09391567013063126556234877116459537e-02L),
         static_cast<storage_type>(2.63549866150321372619018152952991449e-02L),
         static_cast<storage_type>(1.13937985010262879479029641132347736e-02L),
      };
      return data;
   }
};
#else
template <class T>
class gauss_detail<T, 25, 0>
{
   using storage_type = typename gauss_constant_category<T>::storage_type;
public:
   static std::array<storage_type, 13> const & abscissa()
   {
      static const std::array<storage_type, 13> data = {
         static_cast<storage_type>(0.00000000000000000000000000000000000e+00Q),
         static_cast<storage_type>(1.22864692610710396387359818808036806e-01Q),
         static_cast<storage_type>(2.43866883720988432045190362797451586e-01Q),
         static_cast<storage_type>(3.61172305809387837735821730127640667e-01Q),
         static_cast<storage_type>(4.73002731445714960522182115009192041e-01Q),
         static_cast<storage_type>(5.77662930241222967723689841612654067e-01Q),
         static_cast<storage_type>(6.73566368473468364485120633247622176e-01Q),
         static_cast<storage_type>(7.59259263037357630577282865204360976e-01Q),
         static_cast<storage_type>(8.33442628760834001421021108693569569e-01Q),
         static_cast<storage_type>(8.94991997878275368851042006782804954e-01Q),
         static_cast<storage_type>(9.42974571228974339414011169658470532e-01Q),
         static_cast<storage_type>(9.76663921459517511498315386479594068e-01Q),
         static_cast<storage_type>(9.95556969790498097908784946893901617e-01Q),
      };
      return data;
   }
   static std::array<storage_type, 13> const & weights()
   {
      static const std::array<storage_type, 13> data = {
         static_cast<storage_type>(1.23176053726715451203902873079050142e-01Q),
         static_cast<storage_type>(1.22242442990310041688959518945851506e-01Q),
         static_cast<storage_type>(1.19455763535784772228178126512901047e-01Q),
         static_cast<storage_type>(1.14858259145711648339325545869555809e-01Q),
         static_cast<storage_type>(1.08519624474263653116093957050116619e-01Q),
         static_cast<storage_type>(1.00535949067050644202206890392685827e-01Q),
         static_cast<storage_type>(9.10282619829636498114972207028916534e-02Q),
         static_cast<storage_type>(8.01407003350010180132349596691113023e-02Q),
         static_cast<storage_type>(6.80383338123569172071871856567079686e-02Q),
         static_cast<storage_type>(5.49046959758351919259368915404733242e-02Q),
         static_cast<storage_type>(4.09391567013063126556234877116459537e-02Q),
         static_cast<storage_type>(2.63549866150321372619018152952991449e-02Q),
         static_cast<storage_type>(1.13937985010262879479029641132347736e-02Q),
      };
      return data;
   }
};
#endif
template <class T>
class gauss_detail<T, 25, 4>
{
public:
   static  std::array<T, 13> const & abscissa()
   {
      static  std::array<T, 13> data = { // LCOV_EXCL_START
         BOOST_MATH_HUGE_CONSTANT(T, 0, 0.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000e+00),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 1.2286469261071039638735981880803680553220534604978373842389353789270883496885841582643884994633105537597765980412320e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 2.4386688372098843204519036279745158640563315632598447642113565325038747278585595067977636776325034060327548499765742e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 3.6117230580938783773582173012764066742207834704337506979457877784674538239569654860329531506093761400789294612122812e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 4.7300273144571496052218211500919204133181773846162729090723082769560327584128603010315684778279363544192787010704498e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 5.7766293024122296772368984161265406739573503929151825664548350776102301275263202227671659646579649084013116066120581e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 6.7356636847346836448512063324762217588341672807274931705965696177828773684928421158196368568030932194044282149314388e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 7.5925926303735763057728286520436097638752201889833412091838973544501862882026240760763679724185230331463919586229073e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 8.3344262876083400142102110869356956946096411382352078602086471546171813247709012525322973947759168107133491065937347e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 8.9499199787827536885104200678280495417455484975358390306170168295917151090119945137118600693039178162093726882638296e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 9.4297457122897433941401116965847053190520157060899014192745249713729532254404926130890521815127348327109666786665572e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 9.7666392145951751149831538647959406774537055531440674467098742731616386753588055389644670948300617866819865983054648e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 9.9555696979049809790878494689390161725756264940480817121080493113293348134372793448728802635294700756868258870429256e-01),
      }; // LCOV_EXCL_STOP
      return data;
   }
   static  std::array<T, 13> const & weights()
   {
      static  std::array<T, 13> data = { // LCOV_EXCL_START
         BOOST_MATH_HUGE_CONSTANT(T, 0, 1.2317605372671545120390287307905014243823362751815166539135219731691200794926142128460112517504958377310054583945994e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 1.2224244299031004168895951894585150583505924756305904090758008223203896721918010243033540891078906637115620156845304e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 1.1945576353578477222817812651290104739017670141372642551958788133518409022018773502442869720975271321374348568426235e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 1.1485825914571164833932554586955580864093619166818014959151499003148279667112542256534429898558156273250513652351744e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 1.0851962447426365311609395705011661934007758798672201615649430734883929279360844269339768350029654172135832773427565e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 1.0053594906705064420220689039268582698846609452814190706986904199941294815904602968195565620373258211755226681206658e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 9.1028261982963649811497220702891653380992558959334310970483768967017384678410526902484398142953718885872521590850372e-02),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 8.0140700335001018013234959669111302290225732853675893716201462973612828934801289559457377714225318048243957479325813e-02),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 6.8038333812356917207187185656707968554709494354636562615071226410003654051711473106651522969481873733098761760660898e-02),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 5.4904695975835191925936891540473324160109985553111349048508498244593774678436511895711924079433444763756746828817613e-02),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 4.0939156701306312655623487711645953660845783364104346504698414899297432880215512770478971055110424130123527015425511e-02),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 2.6354986615032137261901815295299144935963281703322468755366165783870934008879499371529821528172928890350362464605104e-02),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 1.1393798501026287947902964113234773603320526292909696448948061116189891729766743355923677112945033505688431618009664e-02),
      }; // LCOV_EXCL_STOP
      return data;
   }
};


#ifndef BOOST_HAS_FLOAT128
template <class T>
class gauss_detail<T, 30, 0>
{
   using storage_type = typename gauss_constant_category<T>::storage_type;
public:
   static std::array<storage_type, 15> const & abscissa()
   {
      static constexpr std::array<storage_type, 15> data = {
         static_cast<storage_type>(5.14718425553176958330252131667225737e-02L),
         static_cast<storage_type>(1.53869913608583546963794672743255920e-01L),
         static_cast<storage_type>(2.54636926167889846439805129817805108e-01L),
         static_cast<storage_type>(3.52704725530878113471037207089373861e-01L),
         static_cast<storage_type>(4.47033769538089176780609900322854000e-01L),
         static_cast<storage_type>(5.36624148142019899264169793311072794e-01L),
         static_cast<storage_type>(6.20526182989242861140477556431189299e-01L),
         static_cast<storage_type>(6.97850494793315796932292388026640068e-01L),
         static_cast<storage_type>(7.67777432104826194917977340974503132e-01L),
         static_cast<storage_type>(8.29565762382768397442898119732501916e-01L),
         static_cast<storage_type>(8.82560535792052681543116462530225590e-01L),
         static_cast<storage_type>(9.26200047429274325879324277080474004e-01L),
         static_cast<storage_type>(9.60021864968307512216871025581797663e-01L),
         static_cast<storage_type>(9.83668123279747209970032581605662802e-01L),
         static_cast<storage_type>(9.96893484074649540271630050918695283e-01L),
      };
      return data;
   }
   static std::array<storage_type, 15> const & weights()
   {
      static constexpr std::array<storage_type, 15> data = {
         static_cast<storage_type>(1.02852652893558840341285636705415044e-01L),
         static_cast<storage_type>(1.01762389748405504596428952168554045e-01L),
         static_cast<storage_type>(9.95934205867952670627802821035694765e-02L),
         static_cast<storage_type>(9.63687371746442596394686263518098651e-02L),
         static_cast<storage_type>(9.21225222377861287176327070876187672e-02L),
         static_cast<storage_type>(8.68997872010829798023875307151257026e-02L),
         static_cast<storage_type>(8.07558952294202153546949384605297309e-02L),
         static_cast<storage_type>(7.37559747377052062682438500221907342e-02L),
         static_cast<storage_type>(6.59742298821804951281285151159623612e-02L),
         static_cast<storage_type>(5.74931562176190664817216894020561288e-02L),
         static_cast<storage_type>(4.84026728305940529029381404228075178e-02L),
         static_cast<storage_type>(3.87991925696270495968019364463476920e-02L),
         static_cast<storage_type>(2.87847078833233693497191796112920436e-02L),
         static_cast<storage_type>(1.84664683110909591423021319120472691e-02L),
         static_cast<storage_type>(7.96819249616660561546588347467362245e-03L),
      };
      return data;
   }
};
#else
template <class T>
class gauss_detail<T, 30, 0>
{
   using storage_type = typename gauss_constant_category<T>::storage_type;
public:
   static std::array<storage_type, 15> const & abscissa()
   {
      static const std::array<storage_type, 15> data = {
         static_cast<storage_type>(5.14718425553176958330252131667225737e-02Q),
         static_cast<storage_type>(1.53869913608583546963794672743255920e-01Q),
         static_cast<storage_type>(2.54636926167889846439805129817805108e-01Q),
         static_cast<storage_type>(3.52704725530878113471037207089373861e-01Q),
         static_cast<storage_type>(4.47033769538089176780609900322854000e-01Q),
         static_cast<storage_type>(5.36624148142019899264169793311072794e-01Q),
         static_cast<storage_type>(6.20526182989242861140477556431189299e-01Q),
         static_cast<storage_type>(6.97850494793315796932292388026640068e-01Q),
         static_cast<storage_type>(7.67777432104826194917977340974503132e-01Q),
         static_cast<storage_type>(8.29565762382768397442898119732501916e-01Q),
         static_cast<storage_type>(8.82560535792052681543116462530225590e-01Q),
         static_cast<storage_type>(9.26200047429274325879324277080474004e-01Q),
         static_cast<storage_type>(9.60021864968307512216871025581797663e-01Q),
         static_cast<storage_type>(9.83668123279747209970032581605662802e-01Q),
         static_cast<storage_type>(9.96893484074649540271630050918695283e-01Q),
      };
      return data;
   }
   static std::array<storage_type, 15> const & weights()
   {
      static const std::array<storage_type, 15> data = {
         static_cast<storage_type>(1.02852652893558840341285636705415044e-01Q),
         static_cast<storage_type>(1.01762389748405504596428952168554045e-01Q),
         static_cast<storage_type>(9.95934205867952670627802821035694765e-02Q),
         static_cast<storage_type>(9.63687371746442596394686263518098651e-02Q),
         static_cast<storage_type>(9.21225222377861287176327070876187672e-02Q),
         static_cast<storage_type>(8.68997872010829798023875307151257026e-02Q),
         static_cast<storage_type>(8.07558952294202153546949384605297309e-02Q),
         static_cast<storage_type>(7.37559747377052062682438500221907342e-02Q),
         static_cast<storage_type>(6.59742298821804951281285151159623612e-02Q),
         static_cast<storage_type>(5.74931562176190664817216894020561288e-02Q),
         static_cast<storage_type>(4.84026728305940529029381404228075178e-02Q),
         static_cast<storage_type>(3.87991925696270495968019364463476920e-02Q),
         static_cast<storage_type>(2.87847078833233693497191796112920436e-02Q),
         static_cast<storage_type>(1.84664683110909591423021319120472691e-02Q),
         static_cast<storage_type>(7.96819249616660561546588347467362245e-03Q),
      };
      return data;
   }
};
#endif
template <class T>
class gauss_detail<T, 30, 4>
{
public:
   static  std::array<T, 15> const & abscissa()
   {
      static  std::array<T, 15> data = { // LCOV_EXCL_START
         BOOST_MATH_HUGE_CONSTANT(T, 0, 5.1471842555317695833025213166722573749141453666569564255160843987964755210427109055870090707285485841217089963590678e-02),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 1.5386991360858354696379467274325592041855197124433846171896298291578714851081610139692310651074078557990111754952062e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 2.5463692616788984643980512981780510788278930330251842616428597508896353156907880290636628138423620257595521678255758e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 3.5270472553087811347103720708937386065363100802142562659418446890026941623319107866436039675211352945165817827083104e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 4.4703376953808917678060990032285400016240759386142440975447738172761535172858420700400688872124189834257262048739699e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 5.3662414814201989926416979331107279416417800693029710545274348291201490861897837863114116009718990258091585830703557e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 6.2052618298924286114047755643118929920736469282952813259505117012433531497488911774115258445532782106478789996137481e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 6.9785049479331579693229238802664006838235380065395465637972284673997672124315996069538163644008904690545069439941341e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 7.6777743210482619491797734097450313169488361723290845320649438736515857017299504505260960258623968420224697596501719e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 8.2956576238276839744289811973250191643906869617034167880695298345365650658958163508295244350814016004371545455777732e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 8.8256053579205268154311646253022559005668914714648423206832605312161626269519165572921583828573210485349058106849548e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 9.2620004742927432587932427708047400408647453682532906091103713367942299565110232681677288015055886244486106298320068e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 9.6002186496830751221687102558179766293035921740392339948566167242493995770706842922718944370380002378239172677454384e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 9.8366812327974720997003258160566280194031785470971136351718001015114429536479104370207597166035471368057762560137209e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 9.9689348407464954027163005091869528334088203811775079010809429780238769521016374081588201955806171741257405095963817e-01),
      }; // LCOV_EXCL_STOP
      return data;
   }
   static  std::array<T, 15> const & weights()
   {
      static  std::array<T, 15> data = { // LCOV_EXCL_START
         BOOST_MATH_HUGE_CONSTANT(T, 0, 1.0285265289355884034128563670541504386837555706492822258631898667601623865660942939262884632188870916503815852709086e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 1.0176238974840550459642895216855404463270628948712684086426094541964251360531767494547599781978391198881693385887696e-01),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 9.9593420586795267062780282103569476529869263666704277221365146183946660389908809018092299289324184705373523229592037e-02),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 9.6368737174644259639468626351809865096406461430160245912994275732837534742003123724951247818104195363343093583583429e-02),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 9.2122522237786128717632707087618767196913234418234107527675047001973047070094168298464052916811907158954949394100501e-02),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 8.6899787201082979802387530715125702576753328743545344012222129882153582254261494247955033509639105330215477601953921e-02),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 8.0755895229420215354694938460529730875892803708439299890258593706051180567026345604212402769217808080749416147400962e-02),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 7.3755974737705206268243850022190734153770526037049438941269182374599399314635211710401352716638183270192254236882630e-02),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 6.5974229882180495128128515115962361237442953656660378967031516042143672466094179365819913911598737439478205808271237e-02),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 5.7493156217619066481721689402056128797120670721763134548715799003232147409954376925211999650950125355559974348279846e-02),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 4.8402672830594052902938140422807517815271809197372736345191936791805425677102152797767439563562263454374645955072007e-02),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 3.8799192569627049596801936446347692033200976766395352107732789705946970952769793919055026279035105656340228558382274e-02),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 2.8784707883323369349719179611292043639588894546287496474180122608145988940013933101730206711484171554940392262251283e-02),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 1.8466468311090959142302131912047269096206533968181403371298365514585599521307973654080519029675417955638095832046164e-02),
         BOOST_MATH_HUGE_CONSTANT(T, 0, 7.9681924961666056154658834746736224504806965871517212294851633569200384329013332941536616922861735209846506562158817e-03),
      }; // LCOV_EXCL_STOP
      return data;
   }
};

}

template <class Real, unsigned N, class Policy = boost::math::policies::policy<> >
class gauss : public detail::gauss_detail<Real, N, detail::gauss_constant_category<Real>::value>
{
   typedef detail::gauss_detail<Real, N, detail::gauss_constant_category<Real>::value> base;
public:

   template <class F>
   static auto integrate(F f, Real* pL1 = nullptr)->decltype(std::declval<F>()(std::declval<Real>()))
   {
     // In many math texts, K represents the field of real or complex numbers.
     // Too bad we can't put blackboard bold into C++ source!
      typedef decltype(f(Real(0))) K;
      static_assert(!std::is_integral<K>::value,
                   "The return type cannot be integral, it must be either a real or complex floating point type.");
      using std::abs;
      unsigned non_zero_start = 1;
      K result = Real(0);
      if (N & 1) {
         result = f(Real(0)) * static_cast<Real>(base::weights()[0]);
      }
      else {
         result = 0;
         non_zero_start = 0;
      }
      Real L1 = abs(result);
      for (unsigned i = non_zero_start; i < base::abscissa().size(); ++i)
      {
         K fp = f(static_cast<Real>(base::abscissa()[i]));
         K fm = f(static_cast<Real>(-base::abscissa()[i]));
         result += (fp + fm) * static_cast<Real>(base::weights()[i]);
         L1 += (abs(fp) + abs(fm)) * static_cast<Real>(base::weights()[i]);
      }
      if (pL1)
         *pL1 = L1;
      return result;
   }
   template <class F>
   static auto integrate(F f, Real a, Real b, Real* pL1 = nullptr)->decltype(std::declval<F>()(std::declval<Real>()))
   {
      typedef decltype(f(a)) K;
      static const char* function = "boost::math::quadrature::gauss<%1%>::integrate(f, %1%, %1%)";
      if (!(boost::math::isnan)(a) && !(boost::math::isnan)(b))
      {
         // Infinite limits:
         Real min_inf = -tools::max_value<Real>();
         if ((a <= min_inf) && (b >= tools::max_value<Real>()))
         {
            auto u = [&](const Real& t)->K
            {
               Real t_sq = t*t;
               Real inv = 1 / (1 - t_sq);
               K res = f(t*inv)*(1 + t_sq)*inv*inv;
               return res;
            };
            return integrate(u, pL1);
         }

         // Right limit is infinite:
         if ((boost::math::isfinite)(a) && (b >= tools::max_value<Real>()))
         {
            auto u = [&](const Real& t)->K
            {
               Real z = 1 / (t + 1);
               Real arg = 2 * z + a - 1;
               K res = f(arg)*z*z;
               return res;
            };
            K Q = Real(2) * integrate(u, pL1);
            if (pL1)
            {
               *pL1 *= 2;
            }
            return Q;
         }

         if ((boost::math::isfinite)(b) && (a <= -tools::max_value<Real>()))
         {
            auto v = [&](const Real& t)->K
            {
               Real z = 1 / (t + 1);
               Real arg = 2 * z - 1;
               K res = f(b - arg) * z * z;
               return res;
            };
            K Q = Real(2) * integrate(v, pL1);
            if (pL1)
            {
               *pL1 *= 2;
            }
            return Q;
         }

         if ((boost::math::isfinite)(a) && (boost::math::isfinite)(b))
         {
            if (a == b)
            {
               return K(0);
            }
            if (b < a)
            {
               return -integrate(f, b, a, pL1);
            }
            Real avg = (a + b)*constants::half<Real>();
            Real scale = (b - a)*constants::half<Real>();

            auto u = [&](Real z)->K
            {
               return f(avg + scale*z);
            };
            K Q = scale*integrate(u, pL1);

            if (pL1)
            {
               *pL1 *= scale;
            }
            return Q;
         }
      }
      return static_cast<K>(policies::raise_domain_error(function, "The domain of integration is not sensible; please check the bounds.", a, Policy()));
   }
};

} // namespace quadrature
} // namespace math
} // namespace boost

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif // BOOST_MATH_QUADRATURE_GAUSS_HPP
