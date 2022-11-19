#include "ColorPrimaries.h"

/*
=============================================================================
	ACES: Academy Color Encoding System
	https://github.com/ampas/aces-dev/tree/v1.0

	License Terms for Academy Color Encoding System Components

	Academy Color Encoding System (ACES) software and tools are provided by the Academy under
	the following terms and conditions: A worldwide, royalty-free, non-exclusive right to copy, modify, create
	derivatives, and use, in source and binary forms, is hereby granted, subject to acceptance of this license.

	Copyright © 2013 Academy of Motion Picture Arts and Sciences (A.M.P.A.S.). Portions contributed by
	others as indicated. All rights reserved.

	Performance of any of the aforementioned acts indicates acceptance to be bound by the following
	terms and conditions:

	 *	Copies of source code, in whole or in part, must retain the above copyright
		notice, this list of conditions and the Disclaimer of Warranty.
	 *	Use in binary form must retain the above copyright notice, this list of
		conditions and the Disclaimer of Warranty in the documentation and/or other
		materials provided with the distribution.
	 *	Nothing in this license shall be deemed to grant any rights to trademarks,
		copyrights, patents, trade secrets or any other intellectual property of
		A.M.P.A.S. or any contributors, except as expressly stated herein.
	 *	Neither the name "A.M.P.A.S." nor the name of any other contributors to this
		software may be used to endorse or promote products derivative of or based on
		this software without express prior written permission of A.M.P.A.S. or the
		contributors, as appropriate.

	This license shall be construed pursuant to the laws of the State of California,
	and any disputes related thereto shall be subject to the jurisdiction of the courts therein.

	Disclaimer of Warranty: THIS SOFTWARE IS PROVIDED BY A.M.P.A.S. AND CONTRIBUTORS "AS
	IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND
	NON-INFRINGEMENT ARE DISCLAIMED. IN NO EVENT SHALL A.M.P.A.S., OR ANY
	CONTRIBUTORS OR DISTRIBUTORS, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
	SPECIAL, EXEMPLARY, RESITUTIONARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
	NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
	OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
	NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
	EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

	WITHOUT LIMITING THE GENERALITY OF THE FOREGOING, THE ACADEMY SPECIFICALLY
	DISCLAIMS ANY REPRESENTATIONS OR WARRANTIES WHATSOEVER RELATED TO PATENT OR
	OTHER INTELLECTUAL PROPERTY RIGHTS IN THE ACADEMY COLOR ENCODING SYSTEM, OR
	APPLICATIONS THEREOF, HELD BY PARTIES OTHER THAN A.M.P.A.S.,WHETHER DISCLOSED
	OR UNDISCLOSED.
=============================================================================
*/

glm::vec3 XYZ_to_xyY(glm::vec3 XYZ)
{
	glm::vec3 xyY;

	double divisor = XYZ[0] + XYZ[1] + XYZ[2];
	if (divisor == 0.0)
	{
		divisor = 1e-10;
	}

	xyY[0] = XYZ[0] / divisor;
	xyY[1] = XYZ[1] / divisor;
	xyY[2] = XYZ[1];

	return xyY;
}

glm::vec3 xyY_to_XYZ(glm::vec3 xyY)
{
	glm::vec3 XYZ;

	XYZ[0] = xyY[0] * xyY[2] / glm::max((double)xyY[1], 1e-10);
	XYZ[1] = xyY[2];
	XYZ[2] = (1.0 - xyY[0] - xyY[1]) * xyY[2] / glm::max((double)xyY[1], 1e-10);

	return XYZ;
}

//

glm::mat3 RGB_to_XYZ(const Chromaticities& chroma, double Y)
{
	// X and Z values of RGB value (1, 1, 1), or "white"

	double X = chroma.white.x * Y / chroma.white.y;
	double Z = (1 - chroma.white.x - chroma.white.y) * Y / chroma.white.y;

	// Scale factors for matrix rows

	double d = chroma.red.x   * (chroma.blue.y  - chroma.green.y) +
				chroma.blue.x  * (chroma.green.y - chroma.red.y) +
				chroma.green.x * (chroma.red.y   - chroma.blue.y);

	double Sr = (X * (chroma.blue.y - chroma.green.y) -
				chroma.green.x * (Y * (chroma.blue.y - 1) +
				chroma.blue.y  * (X + Z)) +
				chroma.blue.x  * (Y * (chroma.green.y - 1) +
				chroma.green.y * (X + Z))) / d;

	double Sg = (X * (chroma.red.y - chroma.blue.y) +
				chroma.red.x   * (Y * (chroma.blue.y - 1) +
				chroma.blue.y  * (X + Z)) -
				chroma.blue.x  * (Y * (chroma.red.y - 1) +
				chroma.red.y   * (X + Z))) / d;

	double Sb = (X * (chroma.green.y - chroma.red.y) -
				chroma.red.x   * (Y * (chroma.green.y - 1) +
				chroma.green.y * (X + Z)) +
				chroma.green.x * (Y * (chroma.red.y - 1) +
				chroma.red.y   * (X + Z))) / d;

	// Assemble the matrix

	glm::mat3 M;

	M[0][0] = Sr * chroma.red.x;
	M[0][1] = Sr * chroma.red.y;
	M[0][2] = Sr * (1 - chroma.red.x - chroma.red.y);

	M[1][0] = Sg * chroma.green.x;
	M[1][1] = Sg * chroma.green.y;
	M[1][2] = Sg * (1 - chroma.green.x - chroma.green.y);

	M[2][0] = Sb * chroma.blue.x;
	M[2][1] = Sb * chroma.blue.y;
	M[2][2] = Sb * (1 - chroma.blue.x - chroma.blue.y);

	return M;
}

glm::mat3 XYZ_to_RGB(const Chromaticities& chroma, double Y)
{
    return glm::inverse(RGB_to_XYZ(chroma, Y));
}

//

glm::mat3 chromaticAdaptationMatrix(const glm::vec2& source, const glm::vec2& destination)
{
	const glm::mat3 ConeResponseBradford = {
		   0.89510, -0.75020,  0.03890,
		   0.26640,  1.71350, -0.06850,
		  -0.16140,  0.03670,  1.02960
	};

	glm::vec3 source_xyY = glm::vec3(source, 1.0);
	glm::vec3 destination_xyY = glm::vec3(destination, 1.0);

	glm::vec3 source_XYZ = xyY_to_XYZ(source_xyY);
	glm::vec3 destination_XYZ = xyY_to_XYZ(destination_xyY);

	//

	glm::vec3 source_RhoGammaBeta = ConeResponseBradford * source_XYZ;
	glm::vec3 destination_RhoGammaBeta = ConeResponseBradford * destination_XYZ;

	glm::mat3 Ma = glm::mat3(
	      destination_RhoGammaBeta[0] / source_RhoGammaBeta[0], 0.0, 0.0,
	      0.0, destination_RhoGammaBeta[1] / source_RhoGammaBeta[1], 0.0,
	      0.0, 0.0, destination_RhoGammaBeta[2] / source_RhoGammaBeta[2]
	);

	return glm::inverse(ConeResponseBradford) * Ma * ConeResponseBradford;
};
