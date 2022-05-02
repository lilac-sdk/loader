@echo off

if "%1"=="pull" (

    git pull origin main

    cd sdk/bin
    git pull origin main

    cd ..
    git pull origin main

) else (

    echo ""
    echo "==== geode/sdk ===="
    echo ""

    cd sdk

    git add --all
    git commit -a
    git push origin main

    echo "==== geode/loader ===="
    echo ""

    cd ..

    git add --all
    git commit -a
    git push origin main

)