$fn = 50;

profile_size = 10.5;
solid_height = profile_size/2 + 2;
hole_radius = 2;

module holes()
{
	hole( 10,   0 );
	hole( 20,   0 );
	hole(  0,  10 );
	hole(  0, -10 );
}

module hole( position_x, position_y, radius )
{
	translate([ position_x, position_y, -100 ])
		linear_extrude( height = 200 )
			circle( hole_radius );
}

module solid()
{
	translate([ 10, 0, 0 ])
		linear_extrude( solid_height )
			circle( 20, $fn = 7 );
}

module axis()
{
	rotate([ 0, 90, 0 ])
		translate([ 0, 0, profile_size/2 ])
			linear_extrude( 280 )
				square( profile_size, center = true );
	rotate([ 90, 0, 0 ])
		linear_extrude( 360, center = true )
			square( profile_size, center = true );
}

module base()
{
	difference()
	{
		solid();
		#axis();
	}
}

module angle()
{
	difference()
	{
		base();
		holes();
	}
}

//rotate([ 0, 180, 0 ])
angle();
