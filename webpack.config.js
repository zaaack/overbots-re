const path = require('path')

module.exports = {
  entry: './src/overbots.re',
  output: {
    filename: 'out.js',
    path: path.resolve(__dirname, 'build'),
    publicPath: '/build'
  },
  module: {
    rules: [
      {
        test: /\.(re|ml)$/,
        use: [
          {
            loader: 'bs-loader',
            // options: {
            //   module: 'es6'
            // }
          }
        ]
      }, {
        test: /\.scss$/,
        use: [
          {
            loader: 'style-loader'
          }, {
            loader: 'css-loader'
          }, {
            loader: 'sass-loader',
            options: {
              includePaths: []
            }
          }
        ]
      }
    ]
  },
  resolve: {
    extensions: ['.re', '.ml', '.js']
  }
}
