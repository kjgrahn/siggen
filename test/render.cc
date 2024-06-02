#include <render.h>

#include <orchis.h>

namespace {

    void assert_renders(const std::string& s,
			const std::string& fmt,
			const std::string& res)
    {
	orchis::assert_eq(render(fmt, s), res);
    }
}

namespace rendr {

    using orchis::TC;

    void empty(TC)
    {
	assert_renders("foo bar baz",
		       "",
		       "");
    }

    void no_area(TC)
    {
	assert_renders("foo bar baz", "-----",
				      "-----");
    }

    void one_area(TC)
    {
	assert_renders("foo bar baz", "-##-------",
				      "-  -------");
	assert_renders("foo bar baz", "-###------",
				      "-foo------");
	assert_renders("foo bar baz", "-####-----",
				      "-foo -----");
	assert_renders("foo bar baz", "-######---",
				      "-foo   ---");
	assert_renders("foo bar baz", "-#######--",
				      "-foo bar--");
	assert_renders("foo bar baz", "-########-",
				      "-foo bar -");
    }

    void multiple_areas(TC)
    {
	assert_renders("foo bar baz",
		       "-##-##----------",
		       "-  -  ----------");

	assert_renders("foo bar baz",
		       "-###-##---------",
		       "-foo-  ---------");
	assert_renders("foo bar baz",
		       "-####-##--------",
		       "-foo -  --------");

	assert_renders("foo bar baz",
		       "-####-###-------",
		       "-foo -bar-------");

	assert_renders("foo bar baz",
		       "-####-####------",
		       "-foo -bar ------");

	assert_renders("foo bar baz",
		       "-####-####-##---",
		       "-foo -bar -  ---");

	assert_renders("foo bar baz",
		       "-####-####-###--",
		       "-foo -bar -baz--");

	assert_renders("foo bar baz",
		       "-#########-##---",
		       "-foo bar  -  ---");

	assert_renders("foo bar baz",
		       "-#########-###--",
		       "-foo bar  -baz--");
    }
}
