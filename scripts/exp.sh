cd ../
rm -r experimental_output
mkdir -p experimental_output

make clean
make

declare -a tests=("225"
				"665"
				"884"
				"995")
for i in "${tests[@]}"
for iter in {1..100..1}; do
    for prob in "${tests[@]}" do
        echo "Running program for problem $prob, iteration $iter."
        input="dataset3/${prob}.txt"
        output="experimental_output/${prob}.out"
        ./bin/tp3 $input >> $output
        echo "Done..."
    done
done

make clean