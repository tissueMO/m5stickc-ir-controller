module.exports = {
  presets: [
    [
      "@babel/preset-env",
      {
        useBuiltIns: "usage",
        corejs: "3",
        targets: {
          browsers: ["last 2 versions", "> 3% in JP"],
        },
      },
    ],
  ],
};
