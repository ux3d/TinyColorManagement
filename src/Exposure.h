#ifndef EXPOSURE_H_
#define EXPOSURE_H_

// see https://interplayoflight.wordpress.com/2020/04/19/validating-physical-light-units/
// see https://google.github.io/filament/Filament.md.html#imagingpipeline/physicallybasedcamera
// see https://github.com/troughton/PBRenderer/blob/master/Resources/Shaders/OpenGL/Camera.glsl

// Exposure value see https://en.wikipedia.org/wiki/Exposure_value
//
// EV_s = log2(N^2/t)
//			N is aperture or f-number see https://en.wikipedia.org/wiki/F-number
//			t is exposure time / shutter speed see https://en.wikipedia.org/wiki/Shutter_speed
//
// EV_s = EV_100 + log2(S/100)
//			S is the ISO arithmetic speed see https://en.wikipedia.org/wiki/Film_speed
//
// Solve
// 		EV_100 + log2(S/100)	= log2(N^2/t)
// <=> 	EV_100 					= log2(N^2/t) - log2(S/100)
// <=> 	EV_100 					= log2((N^2/t) / (S/100))
// <=> 	EV_100 					= log2((N^2/t) * (100/S))
double calculateEV100(double N, double t, double S);

// Luminous exposure see https://en.wikipedia.org/wiki/Film_speed
//
// H = q*L*t/N^2
//		L is luminance in cd/m^2
//		q is a depending factor (see more in above link) with a usual value q=0.65
//
// Hsat = 78/Ssat
//
// Solve
// 		q*L*t/N^2 	= 78/S
//		L			= 78/(S*q)*N^2/t
//		L			= 78/(S*q)*2^EV_100			// with S=100 and q=0.65
//		L			= 78/(100*0.65)*2^EV_100
double EV100_2_EXPOSURE(double ev100);

#endif /* EXPOSURE_H_ */
