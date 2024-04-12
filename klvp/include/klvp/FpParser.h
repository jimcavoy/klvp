/// @file FpParser.h
///
/// FpPaser class definition

#pragma once
namespace lcss
{
	/// <summary>
	/// FpParser: Floating Point Parser
	/// Encode and decode floating point values as per MISB ST 1201
	/// using the IMAPB algorithm.
	/// </summary>
	class FpParser
	{
	public:
		FpParser();
		FpParser(double min, double max, int length);

	public:
		/// <summary>
		/// Implements the step one process outlined in 
		/// MISB ST 1201, which sets up the encoding and
		/// decoding algorithm.
		/// </summary>
		/// <param name="min">Minimum range</param>
		/// <param name="max">Maximum range</param>
		/// <param name="length">Precision express in the number of bytes used for
		/// the floating point value.</param>
		void computeConstants(double min, double max, int length);

		/// <summary>
		/// Encodes a double to a byte array.
		/// </summary>
		/// <param name="buffer">The byte array.</param>
		/// <param name="bufsiz">The size of the byte array.</param>
		/// <param name="value">The value </param>
		/// <returns>Returns 1 if the bufsiz is not equal to length.
		/// Returns 2 if value is greater or less than the range(min, max).
		/// Otherwise, return 0 if successful.
		/// </returns>
		int encode(unsigned char* buffer, int bufsiz, double value);

		/// <summary>
		/// Decode an encoded byte array to a double
		/// </summary>
		/// <param name="buffer">Encoded byte array to decode.</param>
		/// <param name="bufsiz">Size of the byte array, buffer.</param>
		/// <returns>Returns the floating point value that was encode in the byte array.</returns>
		double decode(const unsigned char* buffer, int bufsiz);

	private:
		double decodeAsNormalMappedValue(const unsigned char* valueBuffer, int bufsiz) const;

	private:
		double _a;
		double _b;
		double _bPow;
		double _dPow;
		int _length;
		double _sF;
		double _sR;
		double _zOffset;

	};

}
