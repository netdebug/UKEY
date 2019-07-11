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

use strict;
use warnings;
use Path::Tiny;
use Carp;
##  Parse flags.
while ( $ARGV[0] =~ /^-/ ) {
  my $flag = shift @ARGV;
  last if ( $flag eq '--');
  if ( $flag eq '-h' || $flag eq '-help' ) {
    help();
  } elsif ( $flag eq '-n' ) {
    createTemplateProject($ARGV[0]);
  } elsif ( $flag eq '-v' ) {
    print "verbose\n";
  }
  else {
    print STDERR "Usage error; try -h.\n";
    exit 1;
  }
}

sub createTemplateProject {
  my $path = Path::Tiny->cwd;
  print "current working directory : $path \n";
  print "createTemplateProject argv : @_\n";

  my $dir = $_[0];
  unless (path($dir)->exists()) {
    croak "$dir do not exists!";
  }

  my @dirs = (
    $dir.join('','/','include'),
    $dir.join('','/','src')
  );
  createDirs(@dirs);

  my $target = path($dir)->basename();
  my $targetDir = $dir.join('','/','src');
  createSource($target, $targetDir);
}

sub createDirs {
  print "createDirs argv : @_\n";
  foreach my $a (@_) {
    print "$a\n";
    unless(path($a)->exists()) {
      path($a)->mkpath();
    }
  }
}

sub createSource {
  print "createSource argv : @_\n";
  my $t = $_[0]; ## target filename
  my $hpp = $t.join('','.h');
  my $cpp = $t.join('','.cpp');
  my $vcxproj = $t.join('','.vcxproj');
  my $vcxprojfilter = $t.join('','.vcxproj.filters');

  #create files
  my $p = $_[1]; ## srouce code path
  unless (path($p)->exists()) {
    carp "$_[1] do not exists!";
  }
  my @files = (
    $p.join('', '/', $hpp),
    $p.join('', '/', $cpp),
    $p.join('', '/', $vcxproj),
    $p.join('', '/', $vcxprojfilter)
  );
  # push(@files, $_[1].join('', '/', $hpp));
  # push(@files, $_[1].join('', '/', $cpp));
  # push(@files, $_[1].join('', '/', $vcxproj));
  # push(@files, $_[1].join('', '/', $vcxprojfilter));
  foreach my $a (@files) {
    print "$a\n";
    unless (path($a)->exists()) {
      path($a)->touch();
    }
  }
}

sub help {
  print "This script, when run on a directory, copy templete vcxproj and vcxproj.filters
  with params, create include ,src directory , create project file etc.\n";

  print "Usage: mkProj [-h] [-help] [-v] [-n] [dirs...]\n";
  print "   -h or -help print this help text\n";
  print "   -n create template project";
  exit 0;
}
