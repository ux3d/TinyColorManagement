#ifndef CIE_XYZ_CMF_H_
#define CIE_XYZ_CMF_H_

#include <vector>

#include <glm/glm.hpp>

struct CIE_XYZ_cmf {
	double wavelength;
	glm::vec3 XYZ;
};

// CIE 1931
// see http://cvrl.ioo.ucl.ac.uk/cmfs.htm

static const std::vector<CIE_XYZ_cmf> cmf1931 = {
		{360,{0.000129900000,0.000003917000,0.000606100000}},
		{361,{0.000145847000,0.000004393581,0.000680879200}},
		{362,{0.000163802100,0.000004929604,0.000765145600}},
		{363,{0.000184003700,0.000005532136,0.000860012400}},
		{364,{0.000206690200,0.000006208245,0.000966592800}},
		{365,{0.000232100000,0.000006965000,0.001086000000}},
		{366,{0.000260728000,0.000007813219,0.001220586000}},
		{367,{0.000293075000,0.000008767336,0.001372729000}},
		{368,{0.000329388000,0.000009839844,0.001543579000}},
		{369,{0.000369914000,0.000011043230,0.001734286000}},
		{370,{0.000414900000,0.000012390000,0.001946000000}},
		{371,{0.000464158700,0.000013886410,0.002177777000}},
		{372,{0.000518986000,0.000015557280,0.002435809000}},
		{373,{0.000581854000,0.000017442960,0.002731953000}},
		{374,{0.000655234700,0.000019583750,0.003078064000}},
		{375,{0.000741600000,0.000022020000,0.003486000000}},
		{376,{0.000845029600,0.000024839650,0.003975227000}},
		{377,{0.000964526800,0.000028041260,0.004540880000}},
		{378,{0.001094949000,0.000031531040,0.005158320000}},
		{379,{0.001231154000,0.000035215210,0.005802907000}},
		{380,{0.001368000000,0.000039000000,0.006450001000}},
		{381,{0.001502050000,0.000042826400,0.007083216000}},
		{382,{0.001642328000,0.000046914600,0.007745488000}},
		{383,{0.001802382000,0.000051589600,0.008501152000}},
		{384,{0.001995757000,0.000057176400,0.009414544000}},
		{385,{0.002236000000,0.000064000000,0.010549990000}},
		{386,{0.002535385000,0.000072344210,0.011965800000}},
		{387,{0.002892603000,0.000082212240,0.013655870000}},
		{388,{0.003300829000,0.000093508160,0.015588050000}},
		{389,{0.003753236000,0.000106136100,0.017730150000}},
		{390,{0.004243000000,0.000120000000,0.020050010000}},
		{391,{0.004762389000,0.000134984000,0.022511360000}},
		{392,{0.005330048000,0.000151492000,0.025202880000}},
		{393,{0.005978712000,0.000170208000,0.028279720000}},
		{394,{0.006741117000,0.000191816000,0.031897040000}},
		{395,{0.007650000000,0.000217000000,0.036210000000}},
		{396,{0.008751373000,0.000246906700,0.041437710000}},
		{397,{0.010028880000,0.000281240000,0.047503720000}},
		{398,{0.011421700000,0.000318520000,0.054119880000}},
		{399,{0.012869010000,0.000357266700,0.060998030000}},
		{400,{0.014310000000,0.000396000000,0.067850010000}},
		{401,{0.015704430000,0.000433714700,0.074486320000}},
		{402,{0.017147440000,0.000473024000,0.081361560000}},
		{403,{0.018781220000,0.000517876000,0.089153640000}},
		{404,{0.020748010000,0.000572218700,0.098540480000}},
		{405,{0.023190000000,0.000640000000,0.110200000000}},
		{406,{0.026207360000,0.000724560000,0.124613300000}},
		{407,{0.029782480000,0.000825500000,0.141701700000}},
		{408,{0.033880920000,0.000941160000,0.161303500000}},
		{409,{0.038468240000,0.001069880000,0.183256800000}},
		{410,{0.043510000000,0.001210000000,0.207400000000}},
		{411,{0.048995600000,0.001362091000,0.233692100000}},
		{412,{0.055022600000,0.001530752000,0.262611400000}},
		{413,{0.061718800000,0.001720368000,0.294774600000}},
		{414,{0.069212000000,0.001935323000,0.330798500000}},
		{415,{0.077630000000,0.002180000000,0.371300000000}},
		{416,{0.086958110000,0.002454800000,0.416209100000}},
		{417,{0.097176720000,0.002764000000,0.465464200000}},
		{418,{0.108406300000,0.003117800000,0.519694800000}},
		{419,{0.120767200000,0.003526400000,0.579530300000}},
		{420,{0.134380000000,0.004000000000,0.645600000000}},
		{421,{0.149358200000,0.004546240000,0.718483800000}},
		{422,{0.165395700000,0.005159320000,0.796713300000}},
		{423,{0.181983100000,0.005829280000,0.877845900000}},
		{424,{0.198611000000,0.006546160000,0.959439000000}},
		{425,{0.214770000000,0.007300000000,1.039050100000}},
		{426,{0.230186800000,0.008086507000,1.115367300000}},
		{427,{0.244879700000,0.008908720000,1.188497100000}},
		{428,{0.258777300000,0.009767680000,1.258123300000}},
		{429,{0.271807900000,0.010664430000,1.323929600000}},
		{430,{0.283900000000,0.011600000000,1.385600000000}},
		{431,{0.294943800000,0.012573170000,1.442635200000}},
		{432,{0.304896500000,0.013582720000,1.494803500000}},
		{433,{0.313787300000,0.014629680000,1.542190300000}},
		{434,{0.321645400000,0.015715090000,1.584880700000}},
		{435,{0.328500000000,0.016840000000,1.622960000000}},
		{436,{0.334351300000,0.018007360000,1.656404800000}},
		{437,{0.339210100000,0.019214480000,1.685295900000}},
		{438,{0.343121300000,0.020453920000,1.709874500000}},
		{439,{0.346129600000,0.021718240000,1.730382100000}},
		{440,{0.348280000000,0.023000000000,1.747060000000}},
		{441,{0.349599900000,0.024294610000,1.760044600000}},
		{442,{0.350147400000,0.025610240000,1.769623300000}},
		{443,{0.350013000000,0.026958570000,1.776263700000}},
		{444,{0.349287000000,0.028351250000,1.780433400000}},
		{445,{0.348060000000,0.029800000000,1.782600000000}},
		{446,{0.346373300000,0.031310830000,1.782968200000}},
		{447,{0.344262400000,0.032883680000,1.781699800000}},
		{448,{0.341808800000,0.034521120000,1.779198200000}},
		{449,{0.339094100000,0.036225710000,1.775867100000}},
		{450,{0.336200000000,0.038000000000,1.772110000000}},
		{451,{0.333197700000,0.039846670000,1.768258900000}},
		{452,{0.330041100000,0.041768000000,1.764039000000}},
		{453,{0.326635700000,0.043766000000,1.758943800000}},
		{454,{0.322886800000,0.045842670000,1.752466300000}},
		{455,{0.318700000000,0.048000000000,1.744100000000}},
		{456,{0.314025100000,0.050243680000,1.733559500000}},
		{457,{0.308884000000,0.052573040000,1.720858100000}},
		{458,{0.303290400000,0.054980560000,1.705936900000}},
		{459,{0.297257900000,0.057458720000,1.688737200000}},
		{460,{0.290800000000,0.060000000000,1.669200000000}},
		{461,{0.283970100000,0.062601970000,1.647528700000}},
		{462,{0.276721400000,0.065277520000,1.623412700000}},
		{463,{0.268917800000,0.068042080000,1.596022300000}},
		{464,{0.260422700000,0.070911090000,1.564528000000}},
		{465,{0.251100000000,0.073900000000,1.528100000000}},
		{466,{0.240847500000,0.077016000000,1.486111400000}},
		{467,{0.229851200000,0.080266400000,1.439521500000}},
		{468,{0.218407200000,0.083666800000,1.389879900000}},
		{469,{0.206811500000,0.087232800000,1.338736200000}},
		{470,{0.195360000000,0.090980000000,1.287640000000}},
		{471,{0.184213600000,0.094917550000,1.237422300000}},
		{472,{0.173327300000,0.099045840000,1.187824300000}},
		{473,{0.162688100000,0.103367400000,1.138761100000}},
		{474,{0.152283300000,0.107884600000,1.090148000000}},
		{475,{0.142100000000,0.112600000000,1.041900000000}},
		{476,{0.132178600000,0.117532000000,0.994197600000}},
		{477,{0.122569600000,0.122674400000,0.947347300000}},
		{478,{0.113275200000,0.127992800000,0.901453100000}},
		{479,{0.104297900000,0.133452800000,0.856619300000}},
		{480,{0.095640000000,0.139020000000,0.812950100000}},
		{481,{0.087299550000,0.144676400000,0.770517300000}},
		{482,{0.079308040000,0.150469300000,0.729444800000}},
		{483,{0.071717760000,0.156461900000,0.689913600000}},
		{484,{0.064580990000,0.162717700000,0.652104900000}},
		{485,{0.057950010000,0.169300000000,0.616200000000}},
		{486,{0.051862110000,0.176243100000,0.582328600000}},
		{487,{0.046281520000,0.183558100000,0.550416200000}},
		{488,{0.041150880000,0.191273500000,0.520337600000}},
		{489,{0.036412830000,0.199418000000,0.491967300000}},
		{490,{0.032010000000,0.208020000000,0.465180000000}},
		{491,{0.027917200000,0.217119900000,0.439924600000}},
		{492,{0.024144400000,0.226734500000,0.416183600000}},
		{493,{0.020687000000,0.236857100000,0.393882200000}},
		{494,{0.017540400000,0.247481200000,0.372945900000}},
		{495,{0.014700000000,0.258600000000,0.353300000000}},
		{496,{0.012161790000,0.270184900000,0.334857800000}},
		{497,{0.009919960000,0.282293900000,0.317552100000}},
		{498,{0.007967240000,0.295050500000,0.301337500000}},
		{499,{0.006296346000,0.308578000000,0.286168600000}},
		{500,{0.004900000000,0.323000000000,0.272000000000}},
		{501,{0.003777173000,0.338402100000,0.258817100000}},
		{502,{0.002945320000,0.354685800000,0.246483800000}},
		{503,{0.002424880000,0.371698600000,0.234771800000}},
		{504,{0.002236293000,0.389287500000,0.223453300000}},
		{505,{0.002400000000,0.407300000000,0.212300000000}},
		{506,{0.002925520000,0.425629900000,0.201169200000}},
		{507,{0.003836560000,0.444309600000,0.190119600000}},
		{508,{0.005174840000,0.463394400000,0.179225400000}},
		{509,{0.006982080000,0.482939500000,0.168560800000}},
		{510,{0.009300000000,0.503000000000,0.158200000000}},
		{511,{0.012149490000,0.523569300000,0.148138300000}},
		{512,{0.015535880000,0.544512000000,0.138375800000}},
		{513,{0.019477520000,0.565690000000,0.128994200000}},
		{514,{0.023992770000,0.586965300000,0.120075100000}},
		{515,{0.029100000000,0.608200000000,0.111700000000}},
		{516,{0.034814850000,0.629345600000,0.103904800000}},
		{517,{0.041120160000,0.650306800000,0.096667480000}},
		{518,{0.047985040000,0.670875200000,0.089982720000}},
		{519,{0.055378610000,0.690842400000,0.083845310000}},
		{520,{0.063270000000,0.710000000000,0.078249990000}},
		{521,{0.071635010000,0.728185200000,0.073208990000}},
		{522,{0.080462240000,0.745463600000,0.068678160000}},
		{523,{0.089739960000,0.761969400000,0.064567840000}},
		{524,{0.099456450000,0.777836800000,0.060788350000}},
		{525,{0.109600000000,0.793200000000,0.057250010000}},
		{526,{0.120167400000,0.808110400000,0.053904350000}},
		{527,{0.131114500000,0.822496200000,0.050746640000}},
		{528,{0.142367900000,0.836306800000,0.047752760000}},
		{529,{0.153854200000,0.849491600000,0.044898590000}},
		{530,{0.165500000000,0.862000000000,0.042160000000}},
		{531,{0.177257100000,0.873810800000,0.039507280000}},
		{532,{0.189140000000,0.884962400000,0.036935640000}},
		{533,{0.201169400000,0.895493600000,0.034458360000}},
		{534,{0.213365800000,0.905443200000,0.032088720000}},
		{535,{0.225749900000,0.914850100000,0.029840000000}},
		{536,{0.238320900000,0.923734800000,0.027711810000}},
		{537,{0.251066800000,0.932092400000,0.025694440000}},
		{538,{0.263992200000,0.939922600000,0.023787160000}},
		{539,{0.277101700000,0.947225200000,0.021989250000}},
		{540,{0.290400000000,0.954000000000,0.020300000000}},
		{541,{0.303891200000,0.960256100000,0.018718050000}},
		{542,{0.317572600000,0.966007400000,0.017240360000}},
		{543,{0.331438400000,0.971260600000,0.015863640000}},
		{544,{0.345482800000,0.976022500000,0.014584610000}},
		{545,{0.359700000000,0.980300000000,0.013400000000}},
		{546,{0.374083900000,0.984092400000,0.012307230000}},
		{547,{0.388639600000,0.987418200000,0.011301880000}},
		{548,{0.403378400000,0.990312800000,0.010377920000}},
		{549,{0.418311500000,0.992811600000,0.009529306000}},
		{550,{0.433449900000,0.994950100000,0.008749999000}},
		{551,{0.448795300000,0.996710800000,0.008035200000}},
		{552,{0.464336000000,0.998098300000,0.007381600000}},
		{553,{0.480064000000,0.999112000000,0.006785400000}},
		{554,{0.495971300000,0.999748200000,0.006242800000}},
		{555,{0.512050100000,1.000000000000,0.005749999000}},
		{556,{0.528295900000,0.999856700000,0.005303600000}},
		{557,{0.544691600000,0.999304600000,0.004899800000}},
		{558,{0.561209400000,0.998325500000,0.004534200000}},
		{559,{0.577821500000,0.996898700000,0.004202400000}},
		{560,{0.594500000000,0.995000000000,0.003900000000}},
		{561,{0.611220900000,0.992600500000,0.003623200000}},
		{562,{0.627975800000,0.989742600000,0.003370600000}},
		{563,{0.644760200000,0.986444400000,0.003141400000}},
		{564,{0.661569700000,0.982724100000,0.002934800000}},
		{565,{0.678400000000,0.978600000000,0.002749999000}},
		{566,{0.695239200000,0.974083700000,0.002585200000}},
		{567,{0.712058600000,0.969171200000,0.002438600000}},
		{568,{0.728828400000,0.963856800000,0.002309400000}},
		{569,{0.745518800000,0.958134900000,0.002196800000}},
		{570,{0.762100000000,0.952000000000,0.002100000000}},
		{571,{0.778543200000,0.945450400000,0.002017733000}},
		{572,{0.794825600000,0.938499200000,0.001948200000}},
		{573,{0.810926400000,0.931162800000,0.001889800000}},
		{574,{0.826824800000,0.923457600000,0.001840933000}},
		{575,{0.842500000000,0.915400000000,0.001800000000}},
		{576,{0.857932500000,0.907006400000,0.001766267000}},
		{577,{0.873081600000,0.898277200000,0.001737800000}},
		{578,{0.887894400000,0.889204800000,0.001711200000}},
		{579,{0.902318100000,0.879781600000,0.001683067000}},
		{580,{0.916300000000,0.870000000000,0.001650001000}},
		{581,{0.929799500000,0.859861300000,0.001610133000}},
		{582,{0.942798400000,0.849392000000,0.001564400000}},
		{583,{0.955277600000,0.838622000000,0.001513600000}},
		{584,{0.967217900000,0.827581300000,0.001458533000}},
		{585,{0.978600000000,0.816300000000,0.001400000000}},
		{586,{0.989385600000,0.804794700000,0.001336667000}},
		{587,{0.999548800000,0.793082000000,0.001270000000}},
		{588,{1.009089200000,0.781192000000,0.001205000000}},
		{589,{1.018006400000,0.769154700000,0.001146667000}},
		{590,{1.026300000000,0.757000000000,0.001100000000}},
		{591,{1.033982700000,0.744754100000,0.001068800000}},
		{592,{1.040986000000,0.732422400000,0.001049400000}},
		{593,{1.047188000000,0.720003600000,0.001035600000}},
		{594,{1.052466700000,0.707496500000,0.001021200000}},
		{595,{1.056700000000,0.694900000000,0.001000000000}},
		{596,{1.059794400000,0.682219200000,0.000968640000}},
		{597,{1.061799200000,0.669471600000,0.000929920000}},
		{598,{1.062806800000,0.656674400000,0.000886880000}},
		{599,{1.062909600000,0.643844800000,0.000842560000}},
		{600,{1.062200000000,0.631000000000,0.000800000000}},
		{601,{1.060735200000,0.618155500000,0.000760960000}},
		{602,{1.058443600000,0.605314400000,0.000723680000}},
		{603,{1.055224400000,0.592475600000,0.000685920000}},
		{604,{1.050976800000,0.579637900000,0.000645440000}},
		{605,{1.045600000000,0.566800000000,0.000600000000}},
		{606,{1.039036900000,0.553961100000,0.000547866700}},
		{607,{1.031360800000,0.541137200000,0.000491600000}},
		{608,{1.022666200000,0.528352800000,0.000435400000}},
		{609,{1.013047700000,0.515632300000,0.000383466700}},
		{610,{1.002600000000,0.503000000000,0.000340000000}},
		{611,{0.991367500000,0.490468800000,0.000307253300}},
		{612,{0.979331400000,0.478030400000,0.000283160000}},
		{613,{0.966491600000,0.465677600000,0.000265440000}},
		{614,{0.952847900000,0.453403200000,0.000251813300}},
		{615,{0.938400000000,0.441200000000,0.000240000000}},
		{616,{0.923194000000,0.429080000000,0.000229546700}},
		{617,{0.907244000000,0.417036000000,0.000220640000}},
		{618,{0.890502000000,0.405032000000,0.000211960000}},
		{619,{0.872920000000,0.393032000000,0.000202186700}},
		{620,{0.854449900000,0.381000000000,0.000190000000}},
		{621,{0.835084000000,0.368918400000,0.000174213300}},
		{622,{0.814946000000,0.356827200000,0.000155640000}},
		{623,{0.794186000000,0.344776800000,0.000135960000}},
		{624,{0.772954000000,0.332817600000,0.000116853300}},
		{625,{0.751400000000,0.321000000000,0.000100000000}},
		{626,{0.729583600000,0.309338100000,0.000086133330}},
		{627,{0.707588800000,0.297850400000,0.000074600000}},
		{628,{0.685602200000,0.286593600000,0.000065000000}},
		{629,{0.663810400000,0.275624500000,0.000056933330}},
		{630,{0.642400000000,0.265000000000,0.000049999990}},
		{631,{0.621514900000,0.254763200000,0.000044160000}},
		{632,{0.601113800000,0.244889600000,0.000039480000}},
		{633,{0.581105200000,0.235334400000,0.000035720000}},
		{634,{0.561397700000,0.226052800000,0.000032640000}},
		{635,{0.541900000000,0.217000000000,0.000030000000}},
		{636,{0.522599500000,0.208161600000,0.000027653330}},
		{637,{0.503546400000,0.199548800000,0.000025560000}},
		{638,{0.484743600000,0.191155200000,0.000023640000}},
		{639,{0.466193900000,0.182974400000,0.000021813330}},
		{640,{0.447900000000,0.175000000000,0.000020000000}},
		{641,{0.429861300000,0.167223500000,0.000018133330}},
		{642,{0.412098000000,0.159646400000,0.000016200000}},
		{643,{0.394644000000,0.152277600000,0.000014200000}},
		{644,{0.377533300000,0.145125900000,0.000012133330}},
		{645,{0.360800000000,0.138200000000,0.000010000000}},
		{646,{0.344456300000,0.131500300000,0.000007733333}},
		{647,{0.328516800000,0.125024800000,0.000005400000}},
		{648,{0.313019200000,0.118779200000,0.000003200000}},
		{649,{0.298001100000,0.112769100000,0.000001333333}},
		{650,{0.283500000000,0.107000000000,0.000000000000}},
		{651,{0.269544800000,0.101476200000,0.000000000000}},
		{652,{0.256118400000,0.096188640000,0.000000000000}},
		{653,{0.243189600000,0.091122960000,0.000000000000}},
		{654,{0.230727200000,0.086264850000,0.000000000000}},
		{655,{0.218700000000,0.081600000000,0.000000000000}},
		{656,{0.207097100000,0.077120640000,0.000000000000}},
		{657,{0.195923200000,0.072825520000,0.000000000000}},
		{658,{0.185170800000,0.068710080000,0.000000000000}},
		{659,{0.174832300000,0.064769760000,0.000000000000}},
		{660,{0.164900000000,0.061000000000,0.000000000000}},
		{661,{0.155366700000,0.057396210000,0.000000000000}},
		{662,{0.146230000000,0.053955040000,0.000000000000}},
		{663,{0.137490000000,0.050673760000,0.000000000000}},
		{664,{0.129146700000,0.047549650000,0.000000000000}},
		{665,{0.121200000000,0.044580000000,0.000000000000}},
		{666,{0.113639700000,0.041758720000,0.000000000000}},
		{667,{0.106465000000,0.039084960000,0.000000000000}},
		{668,{0.099690440000,0.036563840000,0.000000000000}},
		{669,{0.093330610000,0.034200480000,0.000000000000}},
		{670,{0.087400000000,0.032000000000,0.000000000000}},
		{671,{0.081900960000,0.029962610000,0.000000000000}},
		{672,{0.076804280000,0.028076640000,0.000000000000}},
		{673,{0.072077120000,0.026329360000,0.000000000000}},
		{674,{0.067686640000,0.024708050000,0.000000000000}},
		{675,{0.063600000000,0.023200000000,0.000000000000}},
		{676,{0.059806850000,0.021800770000,0.000000000000}},
		{677,{0.056282160000,0.020501120000,0.000000000000}},
		{678,{0.052971040000,0.019281080000,0.000000000000}},
		{679,{0.049818610000,0.018120690000,0.000000000000}},
		{680,{0.046770000000,0.017000000000,0.000000000000}},
		{681,{0.043784050000,0.015903790000,0.000000000000}},
		{682,{0.040875360000,0.014837180000,0.000000000000}},
		{683,{0.038072640000,0.013810680000,0.000000000000}},
		{684,{0.035404610000,0.012834780000,0.000000000000}},
		{685,{0.032900000000,0.011920000000,0.000000000000}},
		{686,{0.030564190000,0.011068310000,0.000000000000}},
		{687,{0.028380560000,0.010273390000,0.000000000000}},
		{688,{0.026344840000,0.009533311000,0.000000000000}},
		{689,{0.024452750000,0.008846157000,0.000000000000}},
		{690,{0.022700000000,0.008210000000,0.000000000000}},
		{691,{0.021084290000,0.007623781000,0.000000000000}},
		{692,{0.019599880000,0.007085424000,0.000000000000}},
		{693,{0.018237320000,0.006591476000,0.000000000000}},
		{694,{0.016987170000,0.006138485000,0.000000000000}},
		{695,{0.015840000000,0.005723000000,0.000000000000}},
		{696,{0.014790640000,0.005343059000,0.000000000000}},
		{697,{0.013831320000,0.004995796000,0.000000000000}},
		{698,{0.012948680000,0.004676404000,0.000000000000}},
		{699,{0.012129200000,0.004380075000,0.000000000000}},
		{700,{0.011359160000,0.004102000000,0.000000000000}},
		{701,{0.010629350000,0.003838453000,0.000000000000}},
		{702,{0.009938846000,0.003589099000,0.000000000000}},
		{703,{0.009288422000,0.003354219000,0.000000000000}},
		{704,{0.008678854000,0.003134093000,0.000000000000}},
		{705,{0.008110916000,0.002929000000,0.000000000000}},
		{706,{0.007582388000,0.002738139000,0.000000000000}},
		{707,{0.007088746000,0.002559876000,0.000000000000}},
		{708,{0.006627313000,0.002393244000,0.000000000000}},
		{709,{0.006195408000,0.002237275000,0.000000000000}},
		{710,{0.005790346000,0.002091000000,0.000000000000}},
		{711,{0.005409826000,0.001953587000,0.000000000000}},
		{712,{0.005052583000,0.001824580000,0.000000000000}},
		{713,{0.004717512000,0.001703580000,0.000000000000}},
		{714,{0.004403507000,0.001590187000,0.000000000000}},
		{715,{0.004109457000,0.001484000000,0.000000000000}},
		{716,{0.003833913000,0.001384496000,0.000000000000}},
		{717,{0.003575748000,0.001291268000,0.000000000000}},
		{718,{0.003334342000,0.001204092000,0.000000000000}},
		{719,{0.003109075000,0.001122744000,0.000000000000}},
		{720,{0.002899327000,0.001047000000,0.000000000000}},
		{721,{0.002704348000,0.000976589600,0.000000000000}},
		{722,{0.002523020000,0.000911108800,0.000000000000}},
		{723,{0.002354168000,0.000850133200,0.000000000000}},
		{724,{0.002196616000,0.000793238400,0.000000000000}},
		{725,{0.002049190000,0.000740000000,0.000000000000}},
		{726,{0.001910960000,0.000690082700,0.000000000000}},
		{727,{0.001781438000,0.000643310000,0.000000000000}},
		{728,{0.001660110000,0.000599496000,0.000000000000}},
		{729,{0.001546459000,0.000558454700,0.000000000000}},
		{730,{0.001439971000,0.000520000000,0.000000000000}},
		{731,{0.001340042000,0.000483913600,0.000000000000}},
		{732,{0.001246275000,0.000450052800,0.000000000000}},
		{733,{0.001158471000,0.000418345200,0.000000000000}},
		{734,{0.001076430000,0.000388718400,0.000000000000}},
		{735,{0.000999949300,0.000361100000,0.000000000000}},
		{736,{0.000928735800,0.000335383500,0.000000000000}},
		{737,{0.000862433200,0.000311440400,0.000000000000}},
		{738,{0.000800750300,0.000289165600,0.000000000000}},
		{739,{0.000743396000,0.000268453900,0.000000000000}},
		{740,{0.000690078600,0.000249200000,0.000000000000}},
		{741,{0.000640515600,0.000231301900,0.000000000000}},
		{742,{0.000594502100,0.000214685600,0.000000000000}},
		{743,{0.000551864600,0.000199288400,0.000000000000}},
		{744,{0.000512429000,0.000185047500,0.000000000000}},
		{745,{0.000476021300,0.000171900000,0.000000000000}},
		{746,{0.000442453600,0.000159778100,0.000000000000}},
		{747,{0.000411511700,0.000148604400,0.000000000000}},
		{748,{0.000382981400,0.000138301600,0.000000000000}},
		{749,{0.000356649100,0.000128792500,0.000000000000}},
		{750,{0.000332301100,0.000120000000,0.000000000000}},
		{751,{0.000309758600,0.000111859500,0.000000000000}},
		{752,{0.000288887100,0.000104322400,0.000000000000}},
		{753,{0.000269539400,0.000097335600,0.000000000000}},
		{754,{0.000251568200,0.000090845870,0.000000000000}},
		{755,{0.000234826100,0.000084800000,0.000000000000}},
		{756,{0.000219171000,0.000079146670,0.000000000000}},
		{757,{0.000204525800,0.000073858000,0.000000000000}},
		{758,{0.000190840500,0.000068916000,0.000000000000}},
		{759,{0.000178065400,0.000064302670,0.000000000000}},
		{760,{0.000166150500,0.000060000000,0.000000000000}},
		{761,{0.000155023600,0.000055981870,0.000000000000}},
		{762,{0.000144621900,0.000052225600,0.000000000000}},
		{763,{0.000134909800,0.000048718400,0.000000000000}},
		{764,{0.000125852000,0.000045447470,0.000000000000}},
		{765,{0.000117413000,0.000042400000,0.000000000000}},
		{766,{0.000109551500,0.000039561040,0.000000000000}},
		{767,{0.000102224500,0.000036915120,0.000000000000}},
		{768,{0.000095394450,0.000034448680,0.000000000000}},
		{769,{0.000089023900,0.000032148160,0.000000000000}},
		{770,{0.000083075270,0.000030000000,0.000000000000}},
		{771,{0.000077512690,0.000027991250,0.000000000000}},
		{772,{0.000072313040,0.000026113560,0.000000000000}},
		{773,{0.000067457780,0.000024360240,0.000000000000}},
		{774,{0.000062928440,0.000022724610,0.000000000000}},
		{775,{0.000058706520,0.000021200000,0.000000000000}},
		{776,{0.000054770280,0.000019778550,0.000000000000}},
		{777,{0.000051099180,0.000018452850,0.000000000000}},
		{778,{0.000047676540,0.000017216870,0.000000000000}},
		{779,{0.000044485670,0.000016064590,0.000000000000}},
		{780,{0.000041509940,0.000014990000,0.000000000000}},
		{781,{0.000038733240,0.000013987280,0.000000000000}},
		{782,{0.000036142030,0.000013051550,0.000000000000}},
		{783,{0.000033723520,0.000012178180,0.000000000000}},
		{784,{0.000031464870,0.000011362540,0.000000000000}},
		{785,{0.000029353260,0.000010600000,0.000000000000}},
		{786,{0.000027375730,0.000009885877,0.000000000000}},
		{787,{0.000025524330,0.000009217304,0.000000000000}},
		{788,{0.000023793760,0.000008592362,0.000000000000}},
		{789,{0.000022178700,0.000008009133,0.000000000000}},
		{790,{0.000020673830,0.000007465700,0.000000000000}},
		{791,{0.000019272260,0.000006959567,0.000000000000}},
		{792,{0.000017966400,0.000006487995,0.000000000000}},
		{793,{0.000016749910,0.000006048699,0.000000000000}},
		{794,{0.000015616480,0.000005639396,0.000000000000}},
		{795,{0.000014559770,0.000005257800,0.000000000000}},
		{796,{0.000013573870,0.000004901771,0.000000000000}},
		{797,{0.000012654360,0.000004569720,0.000000000000}},
		{798,{0.000011797230,0.000004260194,0.000000000000}},
		{799,{0.000010998440,0.000003971739,0.000000000000}},
		{800,{0.000010253980,0.000003702900,0.000000000000}},
		{801,{0.000009559646,0.000003452163,0.000000000000}},
		{802,{0.000008912044,0.000003218302,0.000000000000}},
		{803,{0.000008308358,0.000003000300,0.000000000000}},
		{804,{0.000007745769,0.000002797139,0.000000000000}},
		{805,{0.000007221456,0.000002607800,0.000000000000}},
		{806,{0.000006732475,0.000002431220,0.000000000000}},
		{807,{0.000006276423,0.000002266531,0.000000000000}},
		{808,{0.000005851304,0.000002113013,0.000000000000}},
		{809,{0.000005455118,0.000001969943,0.000000000000}},
		{810,{0.000005085868,0.000001836600,0.000000000000}},
		{811,{0.000004741466,0.000001712230,0.000000000000}},
		{812,{0.000004420236,0.000001596228,0.000000000000}},
		{813,{0.000004120783,0.000001488090,0.000000000000}},
		{814,{0.000003841716,0.000001387314,0.000000000000}},
		{815,{0.000003581652,0.000001293400,0.000000000000}},
		{816,{0.000003339127,0.000001205820,0.000000000000}},
		{817,{0.000003112949,0.000001124143,0.000000000000}},
		{818,{0.000002902121,0.000001048009,0.000000000000}},
		{819,{0.000002705645,0.000000977058,0.000000000000}},
		{820,{0.000002522525,0.000000910930,0.000000000000}},
		{821,{0.000002351726,0.000000849251,0.000000000000}},
		{822,{0.000002192415,0.000000791721,0.000000000000}},
		{823,{0.000002043902,0.000000738090,0.000000000000}},
		{824,{0.000001905497,0.000000688110,0.000000000000}},
		{825,{0.000001776509,0.000000641530,0.000000000000}},
		{826,{0.000001656215,0.000000598090,0.000000000000}},
		{827,{0.000001544022,0.000000557575,0.000000000000}},
		{828,{0.000001439440,0.000000519808,0.000000000000}},
		{829,{0.000001341977,0.000000484612,0.000000000000}},
		{830,{0.000001251141,0.000000451810,0.000000000000}}
};

glm::vec3 WAVELENGTH_2_XYZ(double wavelength);

#endif /* CIE_XYZ_CMF_H_ */
