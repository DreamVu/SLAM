if ! command -v trtexec &> /dev/null
then
    FILE=/usr/src/tensorrt/bin/trtexec
    if test -f "$FILE"; then
        export PATH=$PATH:/usr/src/tensorrt/bin
    else
        echo "Requirements not complete. Installing..."
        FOLDER=/usr/src/tensorrt/samples/trtexec/
        if [ -d "$FOLDER" ]; then
            sudo chown -R $USER: /usr/src/tensorrt/
            cd /usr/src/tensorrt/samples/trtexec/
            make
            cd -
            if test -f "$FILE"; then
                export PATH=$PATH:/usr/src/tensorrt/bin
            else
                echo "Can't locate trtexec. run: 'sudo find / -name trtexec' and add it to the PATH"
                exit
            fi
        else
            echo "Can't locate trtexec folder. run: 'sudo find / -name tensorrt' and find the folder with trtexec. Go in that folder and run 'make'"
            exit
        fi
    fi
fi

a=1

success=""
failed=""
echo "generating engine for $a"
    
b=1_pal.trt

trtexec --onnx=./generate/1_pal.onnx --fp16 --batch=1 --saveEngine=/usr/local/bin/data/$b --workspace=$1

if [ $? -eq 0 ]; then 
    echo "$b engine created"
    success="$success$b "
else
    echo "$b engine creation failed"
    $failed="$failed$b "
fi
a=`expr $a + 1`


sudo chown -R $USER:$USER /usr/local/bin/data/*.trt 

echo "the following engines were built successfully: $success"

