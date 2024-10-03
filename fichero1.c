#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h> // Para las funciones pipe, fork, read, write, close

	// si pongo el wait en hijo entra con el hola que es de padre luego entra en hijo imprime mensaje del padre y luego en padre 
	void main()
	{
		char buffer[1];
		int fd[2], bytesleidos;
		int fd2[2],bytesleidos2;

	if (pipe(fd) == -1)
	{
		perror("Error al crear el pipe");
		exit(-1);
	}

	if(fork()==0)
	{
		
		if(pipe(fd2)==-1)
		{
			perror("Error al crear el pipe");
			exit(-1);
		}	
			wait(NULL);//pongo el wait en hijo
			char frasehijo[]="Soy el hijo y le mando mensaje a mi padre";
			
			close(fd2[0]);//me va bien si hago el cierre del que no utilizo 
			write(fd[1],frasehijo,strlen(frasehijo));
			close(fd[1]);
			
			bytesleidos2=read(fd2[0],buffer,1);
			while(bytesleidos2>0)
			{
				printf("%c",buffer[0]);
				bytesleidos2=read(fd2[0],buffer,1);
			}
			printf("\n");

			close(fd2[0]);

		}
	else
	{	
		printf("Hola \n");
		
		char frase[]="Soy el padre";
		
		close(fd[1]); //si quito esto no me imprime nada
		write(fd2[1],frase,strlen(frase));// strlen para coger todo hasta longitud
		close(fd2[1]);

		bytesleidos = read(fd[0], buffer, 1);
		while (bytesleidos > 0)
		{
			printf("%c", buffer[0]);//para el buffer que me lo imprima tengo que poner buffer[0] porque estoy en lectura, puse 1 y no me iba 
			bytesleidos = read(fd[0], buffer, 1);
		}
		close(fd[0]); 
	}
	return 0;
}
