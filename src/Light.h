#ifndef LIGHT_H_
#define LIGHT_H_

// Luminous flux (Lichtstrom)
// Symbol:	Φ
// Unit:	lm (Lumen)
// https://en.wikipedia.org/wiki/Luminous_flux
// https://de.wikipedia.org/wiki/Lichtstrom

// Steradian (Steradiant)
// Symbol:	Ω
// Unit:	sr (steradian)
// https://en.wikipedia.org/wiki/Steradian
// https://de.wikipedia.org/wiki/Steradiant

// Luminous intensity (Lichtstaerke)
// Symbol:	I
// Unit:	cd (Candela)
// https://en.wikipedia.org/wiki/Luminous_intensity
// https://de.wikipedia.org/wiki/Lichtst%C3%A4rke_(Photometrie)

// Formula:	I = Φ / Ω

// Illuminance (Beleuchtungsstaerke)
// Symbol:	E
// Unit:	lux
// https://en.wikipedia.org/wiki/Illuminance
// https://de.wikipedia.org/wiki/Beleuchtungsst%C3%A4rke

// Formula:	E = I / d²			d is the distance in meters

// Luminance (Leuchtdichte)
// Symbol:	L
// Unit:	cd / m² (candela per square meter)
// https://en.wikipedia.org/wiki/Luminance
// https://de.wikipedia.org/wiki/Leuchtdichte

// BRDF
// https://en.wikipedia.org/wiki/Bidirectional_reflectance_distribution_function
// https://de.wikipedia.org/wiki/Bidirektionale_Reflexionsverteilungsfunktion

// Formula:	L = f(v, l) * E		v is viewer and l is light

#endif /* LIGHT_H_ */
