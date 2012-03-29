#!/bin/sh

SIMICS_BASE_VERSION=3.0

usage ()
{
     echo
     echo
     echo "This script is used to install Simics base and add-on packages."
     echo
     echo "Usage:"
     echo
     echo "  `basename $0` [OPTIONS]"
     echo
     echo "Options:"
     echo "   -n   install add-on package(s) in a non Simics-base directory."
     echo "        This option is ignored if a base package is installed at "
     echo "        the same time."
     echo "   -h   display this help test"
     echo
}

unset no_base

while getopts nh var ; do
    case $var in
    n)
        no_base=yes
	;;
    ? | h) 
        usage
        exit 2;;
    esac
done

install_error()
{
    echo
    echo "==============================="
    echo
    echo "$1 - Simics was NOT installed correctly."
    echo
    echo "The simics-install.log file may contain more information."
    echo
    exit 1
}

query_user2()
{
    if [ -n "$1" ] ; then
	def=$1
	shift 1
	reps="["$def"]"
	for rep in $@ ; do
	    reps="$reps / $rep"
	done
    fi
    printf "$reps : " >&2
    read ans
    if [ "x$ans" = "x" ] ; then
        ans=$def
    fi
}

query_user()
{
    chk=$@
    while true ; do
        query_user2 $chk
        for a in $chk ; do
            if [ "x$a" = "x$ans" ] ; then
                echo $ans
                return 0
            fi
        done
    done
}

query_user_any()
{
    chk=$@
    query_user2 $chk
    # on platforms where sh support ~ expansion, trigger it
    sh -c "echo $ans"
    return 0
}

get_key_name()
{
    num=$1
    sep=_
    ver=`echo $2 | sed "s/\./_/"`
    echo "tfkey$num$sep$ver"
}

get_key_value()
{
    key=`get_key_name $1 $2`
    echo `eval echo "\\$$key"`
}

set_key_value()
{
    key=`get_key_name $1 $2`
    eval $key=\"$3\"
    export $key
}

get_key()
{
    key_return=`get_key_value $1 $2`
    if [ -z "$key_return" ] ; then
        echo
	echo "No key cached for package $1 version $2"
        echo
        printf "Enter decryption key: "
	read key_return
        set_key_value $1 $2 "$key_return"
    fi
}

get_package_info()
{
    grep -i "^$1:" $2 | awk '{print $2}'
}

get_package_number()
{
    # works for both package and packageinfo files
    echo $1 | sed "s/[a-z\-]*-\([0-9]*\).*/\1/"
}

unpack_package()
{
    ins_path=$1
    install_pkg=$2
    pkg_type=$3

    pkg_name=`get_package_info package-name-full $install_pkg`
    # TODO: backward compat, remove in 3.2
    if [ -z "$pkg_name" ] ; then
	pkg_name=`get_package_info package-name $install_pkg`
    fi
    host=`echo $pkg_name | sed 's/.*-\(.*\)$/\1/'`
    pkg_num=`get_package_number $install_pkg`
    pkg_ver=`get_package_info version $install_pkg`

    p=`ls package-$pkg_num-$pkg_ver-$host.tar.gz.tf 2>> "$LOGFILE"`
    if [ -n "$p" ] ; then
        # encoded package
	get_key $pkg_num $SIMICS_BASE_VERSION
	echo
	echo "Decoding package-$pkg_num"
	p1=`basename $p .tf`
	./$tfdecode $key_return < $p > $p1 2>> "$LOGFILE"
	if [ "$?" != "0" ] ; then
	    rm -f $p1
	    echo
	    echo "The decode program returned an error. Make sure the correct"
	    echo "keys were specified for '$p'"
	    install_error "Package decoding failed"
	fi
    else
	p=`ls package-$pkg_num-$pkg_ver-$host.tar.gz 2>> "$LOGFILE"`
	if [ -n "$p" ] ; then
	    p1=$p
	    keep_p1=yes
	else
	    install_error "No package " $pkg_num " found."
	fi
    fi

    gunzip -t $p1 >> "$LOGFILE"
    if [ "$?" != "0" ] ; then
	rm -f $p1
	echo
	echo "The decoded file in not in gzip format. Make sure the"
	echo "correct keys were specified for '$p'"
	install_error "Package decode failed"
    fi
    gunzip -c $p1 | (cd $ins_path/ ; tar xf - 2>> "$LOGFILE")
    if [ "$?" != "0" ] ; then
	echo
	echo "The decoded tar.gz file wasn't unpacked properly."
	echo "Check log file for possible errors, and make sure there is"
	echo "enought disk space available in $ins_path/."
	rm -f $p1
	install_error "Package extraction using gunzip failed"
    fi
    if [ "x$keep_p1" != "xyes" ] ; then
	rm -f $p1
    fi

    ### copy packageinfo file after successful package install

    pkginfo=packageinfo-pkg-$pkg_num-$pkg_ver-$host
    if [ -f $pkginfo ] ; then
	if [ $pkg_type = base ] ; then
	    cp $pkginfo $ins_path/simics-$vers/packageinfo/$pkg_name
	elif [ -z "$no_base" ] ; then
	    cp $pkginfo $ins_path/packageinfo/$pkg_name
	fi
    else
	echo
	echo "Warning: No package-info file $pkginfo found. Please report."
	echo
    fi
}

finish_install()
{
    echo
    echo "==============================="
    echo
    save_keys=no
    if [ $1 = yes ] ; then
	echo "Simics $vers was successfully installed as $sim_path"
	save_keys=yes
    else
	echo "No Simics base package requested to be installed."
    fi
    echo
    if [ $2 = yes ] ; then
	echo "Simics add-on packages successfully installed in $sim_path"
	save_keys=yes
    else
	echo "No Simics add-on packages requested to be installed."
    fi
    echo
    if [ $1 = yes ] ; then
	echo "Each Simics user can now create a workspace, or update an existing"
	echo "one, by running the following script:"
	echo
	echo "    $sim_path/bin/workspace-setup" | sed 's|//*|/|g'
    fi
    echo

    # only store keys if everything went well, and something was installed
    if [ $save_keys = yes ] ; then
        # create list of variables, echo one at a time
	rm -f $dotfile
	touch $dotfile
	chmod go-rw $dotfile
	keys=`set | grep "^tfkey" | awk -F= '{print $1}'`
	for tf in $keys ; do
	    echo "$tf="\"`eval echo \\$$tf`\" >> $dotfile
	done
	echo "last_install_dir=$3" >> $dotfile
    fi
    exit 0
}

prepare_list()
{
    num=1
    num_str=""
    if [ "$1" = "all" ] ; then
	shift 1
	all_option=all
    else
	all_option=
    fi
    for pp in $@ ; do
	pkgs=`ls $pp* | grep -v '\.tf'`
	pkg=`echo $pkgs| awk '{print $1}'`
	pkgname=`get_package_info package-name-full $pkg | sed 's/\(.*\)\-\(.*\)/\1/'`
        # TODO: backward compat, remove in 3.2
	if [ -z "$pkgname" ] ; then
	    pkgname=`get_package_info package-name $pkg | sed 's/\(.*\)\-\(.*\)/\1/'`
	fi
	printf "$num  %-20s %-10s " $pkgname `get_package_info version $pkg`
	if [ `echo $pkgs | wc -w` -gt 1 ] ; then
	    printf "hosts: "
	else
	    printf "host: "
	fi
	for p in $pkgs ; do
	    printf `echo $p | sed 's/\(.*\)\-\(.*\)/\2 /'`
	    printf ' '
	done
	echo
	num_str="$num_str $num"
	num=`expr $num + 1`
    done
    echo
    ans=`query_user $all_option $num_str none`
    if [ $ans != none ] ; then
	if [ $ans = all ] ; then
	    # all
	    install_pkgs=
	    for p in $@ ; do
		install_pkgs="$install_pkgs `ls $p* | grep -v '\.tf'`"
	    done
	else
	    num=1
	    for p in $@ ; do
		if [ "$ans" = "$num" ] ; then
		    install_pkgs=`ls $p* | grep -v '\.tf'`
		fi
		num=`expr $num + 1`
	    done
	fi
	install_pkg=`echo $install_pkgs | awk '{print $1}'`
    else
	install_pkg=
    fi
}

######################## start here

if [ `uname -p` = sparc ] ; then
    tfdecode=tfdecode-solaris
elif [ a`uname -p` = ax86_64 -o `uname -m` = x86_64 ] ; then
    # some versions of uname does not return x86_64 for -p, try -m as well
    tfdecode=tfdecode-linux64
    tfdecode_compat=tfdecode-linux
else
    tfdecode=tfdecode-linux
fi

clear

echo
echo "Simics 3.0 Installation Script"
echo "==============================="
echo
echo "This script will install the Simics base package, and optional add-on"
echo "packages, in a specified directory. Default is to install in the same"
echo "directory as Simics was installed in the previous time, or in"
echo "/opt/virtutech/."
echo
echo "Encrypted packages only:"
echo "   If the file '$HOME/.simics-tfkeys' exists, it will be searched for"
echo "   keys to use for package decoding. After a successful installation"
echo "   this file will be updated if any new keys have been used."
echo
echo "Default alternatives are enclosed in square brackets ([ ])."
echo

dotfile=$HOME/.simics-tfkeys
if [ -f $dotfile ] ; then
    echo "Using keys from '$dotfile'."
    . $dotfile
    echo
fi

echo "==============================="

echo "Do you want to continue ?"
ans=`query_user yes no`
if [ "$ans" = "no" ] ; then
    install_error "Installation interrupted"
fi

LOGFILE="`pwd`/simics-install.log"
rm -f "$LOGFILE" 2>/dev/null

touch "$LOGFILE" 2>/dev/null
if [ "$?" != "0" ] ; then
    # put log file in /tmp if not allowed to access cwd
    install_error "Current directory not writable."
fi

gunzip_file=`which gunzip 2> /dev/null`
if [ -z "$gunzip_file" ] ; then
    install_error "No 'gunzip' binary found in $PATH."
fi

if [ ! -f ./$tfdecode -a -n "$tfdecode_compat" ] ; then
    tfdecode=$tfdecode_compat
fi

if [ ! -f ./$tfdecode ] ; then
    install_error "No 'tfdecode' binary in package that matches the host."
fi

./$tfdecode 2> /dev/null
if [ $? -ne 0 ] ; then
    install_error "The 'tfdecode' binary does not work on this host."
fi

### uncompress all packageinfo files


pkginfo=`ls packageinfo-*.tf 2>/dev/null | sed "s/\.tf//"`
if [ -n "$pkginfo" ] ; then
    # handle encrypted packageinfo files
    for f in $pkginfo ; do
	if [ ! -f $f ] ; then
	    pkg_num=`get_package_number $f`
	    get_key $pkg_num $SIMICS_BASE_VERSION
	    ./$tfdecode $key_return < $f.tf > $f 2>> "$LOGFILE"
	    if [ "$?" != "0" ] ; then
		rm -f $f
                install_error "Packageinfo decoding failed"
	    fi
	    grep "^name:" $f > /dev/null
	    if [ "$?" != "0" ] ; then
		rm -f $f
                install_error "Packageinfo decoding failed"
            fi
	fi
    done
fi

### find all base packages

pkginfo=`ls packageinfo-* 2>/dev/null | grep -v "\.tf"`
corepkg=`grep -l "^type:.*base" $pkginfo | sed 's/\(.*\)\-\(.*\)/\1/' | sort -u`

### ask user about what base package to install


if [ -n "$corepkg" ] ; then
    echo
    echo "What Simics base package do you want to install?"
    echo

    prepare_list $corepkg
else
    install_pkg=
fi

if [ -n "$install_pkg" ] ; then
    ### ask user about installation directory


    vers=`get_package_info version $install_pkg`
    if [ -z "$last_install_dir" ] ; then
	ins_path="/opt/virtutech"
    else
	ins_path=`dirname $last_install_dir`
    fi
    echo
    echo "Please specify directory to install Simics in: <path>/simics-$vers/"
    ins_path=`query_user_any $ins_path`
    ins_path=`echo $ins_path | sed "s/\/$//"`

    if [ `echo "$ins_path" | wc -w` -gt 1 ] ; then
	echo "Illegal directory name $ins_path" >> "$LOGFILE"
	echo
	install_error "Cannot install in a directory with spaces"
    fi

    # use $ins_path/ to support installing in /

    if [ -d $ins_path/ ] ; then
	true
    elif [ -f $ins_path/ ] ; then
	echo
	install_error "$ins_path/ is not a directory."
    else
	echo
	echo "$ins_path/ does not exist. Create it?"
	ans=`query_user yes no`
	if [ "$ans" = "no" ] ; then
	    install_error "No installation directory"
	fi
	mkdir -p $ins_path/ 2>> "$LOGFILE"
	if [ "$?" != "0" ] ; then
	    install_error "Failed creating directory"
	fi
    fi

    sim_path=$ins_path/simics-$vers/

    echo
    echo "Installing Simics in: $sim_path"

    ### check for existing installations


    # TODO: check for existing Simics installation
    #       if other base package -> error (same package for other host ok)
    #       if same base package -> ask if version change ok
    #       if same version -> error or reinstall?


    ### unpack the base package

    for p in $install_pkgs ; do
	unpack_package $ins_path $p base
    done

    base_installed=yes
else
    base_installed=no
fi


### check for add-on packages


pkginfo=`ls packageinfo-* 2>/dev/null | grep -v "\.tf"`
addonpkg=`grep -l "^type:.*addon" $pkginfo | sed 's/\(.*\)\-\(.*\)/\1/' | sort -u`

if [ -z "$addonpkg" ] ; then
    finish_install $base_installed no $sim_path
fi


### ask user about what add-on packages to install


echo
echo "What Simics add-on package do you want to install?"
echo

prepare_list all $addonpkg

if [ $ans = none ] ; then
    finish_install $base_installed no $sim_path
fi


### ask user about installation directory if no base package installed


if [ -z "$sim_path" ] ; then
    if [ -z "$no_base" ] ; then
	echo
	if [ -z "$last_install_dir" ] ; then
	    base_path=""
	else
	    base_path="$last_install_dir"
	fi
	echo "Please specify existing Simics base directory to install add-on in."
	base_path=`query_user_any $base_path`
	base_path=`echo $base_path | sed "s/\/$//"`

	if [ ! -d $base_path/ ] ; then
	    echo "$base_path/ does not exist."
	    install_error "Illegal Simics base installation directory"
	elif [ ! -f $base_path/Version ] ; then
            # TODO: better way to detect a Simics base install
	    echo "$base_path/ is not a valid Simics base install."
	    install_error "Illegal Simics base installation directory"
	fi
    else
	echo
	echo "Please specify existing directory to install add-on in."
	base_path=`query_user_any`
	base_path=`echo $base_path | sed "s/\/$//"`
	if [ ! -d $base_path/ ] ; then
	    echo "$base_path/ does not exist."
	    install_error "Illegal installation directory"
	fi
    fi
    sim_path=$base_path/
fi


### install add-on packages

### check for existing add-on


# TODO: check for existing add-on
#       if same add-on on other host, only allow same version
#       but allow upgrades of several host packages as the same time

for p in $install_pkgs ; do
    unpack_package $sim_path $p addon
done

finish_install $base_installed yes $sim_path
