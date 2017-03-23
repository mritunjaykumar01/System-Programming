echo -n enter  the name :   
read name
while read line
do 
    IFS=',' read -r -a array <<< "$line"
    a="${array[1],,}"
    name="${name,,}"
    if [[ $a = *"$name"* ]]
        then
        for index in "${!array[@]}"
        do
            case $index in
            1)
            printf "Full Name      : %s\n" "${array[index]}"
            ;;
            2)
            printf "Designation    : %s\n" "${array[index]}"
            ;;
            3)
            printf "Phone No       : %s\n" "${array[index]}"
            ;;
            4)
            printf "Email id       : %s\n" "${array[index]}"
            ;;
            5)
            printf "Room No        : %s\n" "${array[index]}"
            ;;
            esac
        done
    fi
done < phonebook.txt

