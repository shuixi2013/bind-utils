#!/usr/local/bin/perl -w
#
# Copyright (C) 2000  Internet Software Consortium.
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND INTERNET SOFTWARE CONSORTIUM
# DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
# INTERNET SOFTWARE CONSORTIUM BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING
# FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
# NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
# WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

# $Id: spacewhack.pl,v 1.2 2000/08/01 15:25:07 tale Exp $

$0 =~ s%.*/%%;

if (@ARGV != 0) {
	warn "Usage: $0 < list-of-files\n";
	warn "The util/copyrights file is normally used for list-of-files.\n";
	exit(1);
}

$total = 0;

printf "Lines Trimmed:\n";

while (defined($line = <STDIN>)) {
	($file) = split(/\s+/, $line, 2);

        # These are binary and must be ignored.
        next if $file =~ m%/random.data|\.gif$%;
        next if -B $file;

        print "$file\n";

	unless (open(FILEIN, "< $file")) {
		warn "$0: open < $file: $!, skipping\n";
		next;
	}
        
	undef $/;		# Slurp whole file.
	$_ = <FILEIN>;
	$/ = "\n";		# Back to line-at-a-time for <FILES>.

        close(FILEIN);

	$count = s/[ \t]+$//mg;

	next unless $count > 0;

	unless (open(FILEOUT, "> $file")) {
		warn "$0: open > $file: $!, skipping\n";
		next;
	}

	print FILEOUT or die "$0: printing to $file: $!, exiting\n";
        close FILEOUT or die "$0: closing $file: $!, exiting\n";

	printf("%6d lines trimmed in $file\n", $count) if $count > 0;

	$total += $count;
}

printf "%6d TOTAL\n", $total;

exit(0);

