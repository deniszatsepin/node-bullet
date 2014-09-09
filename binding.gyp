{
	"variables": {
		"bullet_root%": "<(module_root_dir)/libbullet",
	},
	"targets": [{
		"target_name": "bullet",
		"sources": [ "<!@(ls -1 src/*.cc)", ],
		'include_dirs': [
			'<!(node -e "require(\'nan\')")',
			'src',
			'<(bullet_root)/src',
		],
		'link_settings': {
			'libraries': [
				'-Wl,-Bstatic',
				'-L<(bullet_root)/src/.libs',
				'-lBulletSoftBody',
				'-lBulletDynamics',
				'-lBulletCollision',
				'-lLinearMath',
				'-Wl,-Bdynamic',
			]
		},
	}]
}
