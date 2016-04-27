$fn = 50;

height = 15;

D = 300;
Dr2 = sqrt( 2 ) * D;

echo( Dr2 );

propeller = 250;
motor_r = 25;
frame_d = 10;

box_height = 25;

axis = [ -1, 1 ];

module rotor()
{
	color( "gold" )
		cylinder( r = motor_r, h = 35 );
	color( "silver" )
		translate([ 0, 0, 34 ])
			cylinder( r1 = 6, r2 = 3, h = 20 );
	color([ 0, 0, 0, 0.05 ])
		translate([ 0, 0, 37 ])
			cylinder( d = propeller, h = 4 );
	color( "silver" )
		rotate([ 0, 180, 90 ])
			translate([ 0, 0, frame_d ])
				linear_extrude( height = 100 )
					square([ 1, 10 ], center = true );
	color( "silver" )
		translate([ 0, 0, - frame_d / 2 ])
			rotate([ 90, 0, 0 ])
				translate([ 0, 0, - motor_r ])
					linear_extrude( height = Dr2 / 2 + motor_r - frame_d / 2 )
						square( frame_d, center = true );
}

module battery()
{
	color( "green" )
		translate([ 0, 0, -9 -frame_d ])
			rotate([ 45, 90, 0 ])
				cube([ 18, 45, 120 ], center = true );
}

module quad_rotor()
{
	for( x = axis )
		for( y = axis )
			translate( D * [ x, y, 0 ] / 2 )
				rotate([ 0, 0, -atan2( x, y ) ])
					rotor();
}

module box()
{
	border = 15;

	rotate( 45 )
		linear_extrude( height = box_height )
			minkowski()
			{
				square( Dr2 - propeller - 2 * border, center = true );
				circle( border );
			}

	echo(  Dr2 - propeller );
}

box();
quad_rotor();
battery();

