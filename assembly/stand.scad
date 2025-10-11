// SPDX-FileCopyrightText: 2025 Hackropole
// SPDX-License-Identifier: CC-BY-4.0

$fn=100;

// Hackropole badge, 3mm above ground
//color("blue") translate([0, 0, 3]) rotate([0, -10, 0]) translate([0, 0, 94/2]) cube([1.6, 94, 94], center=true);

// Badge stand
color("white") difference() {
    union() {
        translate([-3, 20, 0]) cube([6, 20, 6]);
        translate([-3, -20-20, 0]) cube([6, 20, 6]);

        // Back support
        translate([0, 30, 0]) rotate([0, 90-10, 0]) translate([-6, 0, -2]) difference() {
            cylinder(h=2, r=10);
            translate([2, -10, -1]) cube([10, 20, 10]);
        }
        translate([0, -30, 0]) rotate([0, 90-10, 0]) translate([-6, 0, -2]) difference() {
            cylinder(h=2, r=10);
            translate([2, -10, -1]) cube([10, 20, 10]);
        }

        // Prevent tipping
        difference() {
            cylinder(h=4, r=30+2);
            translate([0, 0, -1]) cylinder(h=6, r=30-2);
            translate([0, -40, -1]) cube([40, 80, 6]);
        }
    }
    
    // Badge cutout
    translate([0, 0, 3]) rotate([0, -10, 0]) translate([0, 0, 94/2]) cube([1.6+0.2, 94, 94], center=true);
}
