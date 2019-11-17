cd ../
mkdir -p tests/output
echo -e "Fazendo a limpeza dos objetos e executáveis...\n"
make clean
echo -e "Iniciando compilação...\n"
make
echo -e "\nIniciando testes..."

declare -a tests=("221" 
                "222"
				"223"
                "224"
				"225"
                )

for i in "${tests[@]}"
do
	echo "Testando entrada dataset3/$i.txt"
	./bin/tp2.exe dataset3/$i.txt > tests/output/$i.out
done
