#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

/* Prints usage information for this program to STREAM (typically
   stdout or stderr), and exit the program with EXIT_CODE.  Does not
   return.  */

void print_usage (FILE* stream, int exit_code)
{
  fprintf (stream, "************************  HELP************************\n\n");
  fprintf (stream,
           "  -h  --help             Display this usage information.\n"
           "  -a  --adicao	         Adição. \n"
           "  -s  --subtracao        Subtração.\n"
	         "  -m  --multiplicacao    Multiplicação.\n"
           "  -d  --divisao          Divisão.\n"
           "  Input                  -a X --multiplicacao X .\n");
  exit (exit_code);
}


int main (int argc, char* argv[])
{
  int next_option;

  /* A string listing valid short options letters.  */
  const char* const short_options = "ha:s:m:d:";
  /* An array describing valid long options.  */
  const struct option long_options[] = {
    { "help",     0, NULL, 'h' },
    { "adicao",   1, NULL, 'a' },
    { "subtracao",  1, NULL, 's' },
    { "multiplicacao",  1, NULL, 'm' },
    { "divisao",  1, NULL, 'd' },
    { NULL,       0, NULL, 0   }   /* Required at end of array.  */
  };

  float output_filename = 0;

  do {
    next_option = getopt_long (argc, argv, short_options,
                               long_options, NULL);
    switch (next_option)
    {
      case 'h':   /* -h or --help */

      print_usage (stdout, 0);

      case 'a':
        output_filename = output_filename + atof(optarg);
      break;

      case 's':
        output_filename = output_filename - atof(optarg);
      break;

      case 'm':
     	 output_filename = output_filename * atof(optarg);
     break;

      case 'd':
        if(atoi(optarg) != 0)
        {
  	 output_filename = output_filename / atoi(optarg);
        }else{
  	 	fprintf(stderr,"ERRO, divisao por 0 \n");
  		exit (-1)	;
        }
      break;

    case '?':
      print_usage (stderr, -2);
      output_filename = -1;

    case -1:    /* Done with options.  */
      break;

    default:    /* Something else: unexpected.  */

      abort ();
    }
  }
  while (next_option != -1);

if(output_filename != -1)
  printf("Resultado %f \n", output_filename);

  return 0;
}
