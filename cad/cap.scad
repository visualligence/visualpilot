$fn = 50;

profile_size = 10.6;
wall = 1;
epsilon = 0.001;

difference()
{
	linear_extrude( height = wall + profile_size )
		square( profile_size + 2 * wall, center = true );
	translate([ 0, 0, wall ])
		linear_extrude( height = profile_size + epsilon )
			square( profile_size, center = true );
}
