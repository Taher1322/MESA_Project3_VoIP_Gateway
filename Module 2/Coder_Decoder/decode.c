#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define	SIGN_BIT	(0x80)	/* Sign bit for a A-law byte. */
#define	QUANT_MASK	(0xf)		/* Quantization field mask. */
#define	SEG_SHIFT	(4)	/* Left shift for segment number */
#define BIAS	(0x84)		/* Bias for linear code. */
#define	SEG_MASK	(0x70)		/* Segment field mask. */


/*
 * Snack_Mulaw2Lin() - Convert a u-law value to 16-bit linear PCM
 *
 * First, a biased linear code is derived from the code word. An unbiased
 * output can then be obtained by subtracting 33 from the biased code.
 *
 * Note that this function expects to be passed the complement of the
 * original code word. This is in keeping with ISDN conventions.
 */
short
Snack_Mulaw2Lin(
	unsigned char	u_val)
{
	short t;

	/* Complement to obtain normal u-law value. */
	u_val = ~u_val;

	/*
	 * Extract and bias the quantization bits. Then
	 * shift up by the segment number and subtract out the bias.
	 */
	t = ((u_val & QUANT_MASK) << 3) + BIAS;
	t <<= ((unsigned)u_val & SEG_MASK) >> SEG_SHIFT;

	return ((u_val & SIGN_BIT) ? (BIAS - t) : (t - BIAS));
}
//http://www.topherlee.com/software/pcm-tut-wavformat.html#:~:text=The%20header%20is%20the%20beginning%20of%20a%20WAV,has%20the%20following%20format%3A%20So%2C%20that%27s%20the%20header.
uint8_t header[]={0x52,0x49, 0x46, 0x46, 	//"RIFF" 
	          0xda,0xff, 0x04,0x00,  	//File size
		  0x57,0x41, 0x56, 0x45, 	//WAVE 
		  0x66,0x6d, 0x74,0x20, 	//"fmt"
	          0x10,0x00, 0x00,0x00, 	//16
                  0x01,0x00, 			//1
                  0x01,0x00, 			//2 
                  0x40,0x1f,0x00,0x00, 		//44100 - sample rate
                  0x00,0x7d,0x00,0x00, 		//176400
                  0x02,0x00, 			//4
                  0x10,0x00, 			//16
                  0x64,0x61,0x74,0x61, 		//"data" chunk header
                  0xb6,0xff, 0x04,0x00 		//File sizes
		 }; 

int main(int argc,char* argv[]){
  FILE *InputFilePointer = fopen(argv[1], "rb");      //file pointer for input file
  FILE *OutputFilePointer = fopen(argv[2], "wb+");     //file pointer for output file

  //write header to new output file from read file
  uint32_t i;	
  uint8_t buffer;  
  for(i=0;i<44;i++)
  {                 
	buffer = header[i];
	fwrite(&buffer,sizeof(buffer),1,OutputFilePointer);
  }
  
  uint16_t output;
  if(InputFilePointer != NULL)
  {
    fseek(InputFilePointer,44,SEEK_SET); //move over header data
    while(!feof(InputFilePointer)) //while EOF is not reached
    {
      fread(&buffer,sizeof(buffer),1,InputFilePointer); //read input
      output = Snack_Mulaw2Lin(buffer); //decode audio data
      fwrite(&output,sizeof(output),1,OutputFilePointer); 
    
    }
    fclose(InputFilePointer);
    fclose(OutputFilePointer);
  }
}