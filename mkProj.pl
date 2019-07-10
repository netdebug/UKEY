#!/usr/bin/perl -wi
#
# mkProj.pl
#
# This script, when run on a directory, copy templete vcxproj and vcxproj.filters
# with params, create include ,src directory , create project file etc.
#
# Author: Kevin Yu <anyboo@qq.com>
#
# $Id$

#use strict;
use warnings;

my $dir = "";
my $prefix = "";

my $errorcount = 0;
## my $openssl = $ENV{OPENSSL} || "openssl";
## my $pwd;
my $x509hash = "-subject_hash";
my $crlhash = "-hash";
my $verbose = 0;

##  Parse flags.
while ( $ARGV[0] =~ /^-/ ) {
    my $flag = shift @ARGV;
    last if ( $flag eq '--');
    if ( $flag eq '-old') {
      print "-subject_hash_old\n";
      print "-hash_old\n";
	    ##$x509hash = "-subject_hash_old";
	    ##$crlhash = "-hash_old";
    } elsif ( $flag eq '-h' || $flag eq '-help' ) {
	    help();
    } elsif ( $flag eq '-n' ) {
	    createTemplateProject();
    } elsif ( $flag eq '-v' ) {
	    #$verbose++;
      print "verbose\n";
    }
    else {
	    print STDERR "Usage error; try -h.\n";
	    exit 1;
    }
}

sub createTemplateProject {
  use Path::Tiny;
  $dir = path($ARGV[0])->stringify();
  $path = Path::Tiny->cwd; # path( Cwd::getcwd )
  @paths = path($path)->children();
  # create directory for include / src
  $include = $dir.join('','/','include');
  $src = $dir.join('','/','src');
  $col = 0;

  $target = path($dir)->basename();
  $hpp = $target.join('','.h');
  $cpp = $target.join('','.cpp');
  $vcxproj = $target.join('','.vcxproj');
  $vcxprojfilter = $target.join('','.vcxproj.filter');
  # foreach $fi (@paths) {
  #   $col++;
  #   print "$col $target $include $src $hpp $cpp\n";
  # }
  #create directorys
    my @dirs;
    push(@dirs, $include);
    push(@dirs, $src);
    foreach $a (@dirs) {
      print "$a\n";
      $obj = path($a);
      unless($obj->exists()) {
        $obj->mkpath();
      }
    }

  #create files
  if(path($src)->exists()) {
    my @files;
    push(@files, $src.join('', '/', $hpp));
    push(@files, $src.join('', '/', $cpp));
    push(@files, $src.join('', '/', $vcxproj));
    push(@files, $src.join('', '/', $vcxprojfilter));
    foreach $a (@files) {
        print "$a\n";
        $o = path($a);
        unless($o->exists()){
          $o->touch();
        }
    }
  }

  #print "path($src.join($hpp))";
  #print "path($src.join($cpp))";
  #create .vcxproj/.filter configure file(xml)
  #create project.name.h project.name.cpp
}

sub help {
  print "This script, when run on a directory, copy templete vcxproj and vcxproj.filters
with params, create include ,src directory , create project file etc.\n";

	print "Usage: mkProj [-h] [-help] [-v] [-n] [dirs...]\n";
	print "   -h or -help print this help text\n";
  print "   -n create template project";
	exit 0;
}
