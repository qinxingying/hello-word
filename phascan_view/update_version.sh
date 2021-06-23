#!/bin/sh

echo $1

INCLUDE_DIR=$1

cd ${INCLUDE_DIR}

version=`git log --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset   %s %Cgreen(%cr)%Creset' --abbrev-commit --date=relative | grep "tag:" | head -n 1 | cut -d":" -f2 | cut -d")" -f1 | cut -d"," -f1 | cut -d" " -f2`

echo ${version}

COMMIT_NUMBER=$(git log --pretty=format:'%h'|head -1)
	
if [ -z "${version}" ]; then
	echo "empty version"
	version='0.0.0'
fi

VERSION_MAJOR=$(echo ${version} | awk -F"." '{print $1}')
VERSION_MINOR=$(echo ${version} | awk -F"." '{print $2}')
VERSION_MICRO=$(echo ${version} | awk -F"." '{print $3}')

echo ${INCLUDE_DIR}

echo Mercury-${version}

echo Commit:${COMMIT_NUMBER}

cat > ${INCLUDE_DIR}/version.h << EOF
#ifndef __VERSION_H__
#define __VERSION_H__

#define VERSION "${version}"
#define VER_MAJOR (${VERSION_MAJOR})
#define VER_MINOR (${VERSION_MINOR})
#define VER_MICRO (${VERSION_MICRO})
#define GIT_COMMIT "${COMMIT_NUMBER}"

#endif

EOF

