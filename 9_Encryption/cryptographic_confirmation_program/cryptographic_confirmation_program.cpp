//RSA 암호화로 파일 서명 및 변조 여부 확인 프로그램 구현
/*
RSA 암호화를 이용해 파일에 서명을 하고, 서명된 파일의 변조 여부를 확인하는 프로그램을 작성
- 추후 검증과정에서 사용되는 서명은 별도의 파일로 저장돼야 함
- 이 프로그램은 두 개의 함수를 제공해야 함
    - 원본 파일과 RSA 개인 키의 경로, 서명 파일이 저장될 경로를 전달 인자로 갖는 서명 함수
    - 파일과 RSA 공개 키, 서명 파일의 경로를 전달 인자로 받는 검증 함수
*/

#include <iostream>
#include <string>
#include <assert.h>

#include "rsa.h"
#include "aes.h"
#include "hex.h"
#include "files.h"
#include "osrng.h"

#ifdef USE_BOOST_FILESYSTEM
#  include <boost/filesystem/path.hpp>
#  include <boost/filesystem/operations.hpp>
namespace fs = boost::filesystem;
#else
#  include <filesystem>
#  ifdef FILESYSTEM_EXPERIMENTAL
namespace fs = std::experimental::filesystem;
#  else
namespace fs = std::filesystem;
#  endif
#endif

void encode(
   fs::path const & filepath,
   CryptoPP::BufferedTransformation const & bt)
{
   CryptoPP::FileSink file(filepath.c_str());

   bt.CopyTo(file);
   file.MessageEnd();
}

void encode_private_key(
   fs::path const & filepath,
   CryptoPP::RSA::PrivateKey const & key)
{
   CryptoPP::ByteQueue queue;
   key.DEREncodePrivateKey(queue);

   encode(filepath, queue);
}

void encode_public_key(
   fs::path const & filepath,
   CryptoPP::RSA::PublicKey const & key)
{
   CryptoPP::ByteQueue queue;
   key.DEREncodePublicKey(queue);

   encode(filepath, queue);
}

void decode(
   fs::path const & filepath,
   CryptoPP::BufferedTransformation& bt)
{
   CryptoPP::FileSource file(filepath.c_str(), true);

   file.TransferTo(bt);
   bt.MessageEnd();
}

void decode_private_key(
   fs::path const & filepath,
   CryptoPP::RSA::PrivateKey& key)
{
   CryptoPP::ByteQueue queue;

   decode(filepath, queue);
   key.BERDecodePrivateKey(queue, false, queue.MaxRetrievable());
}

void decode_public_key(
   fs::path const & filepath,
   CryptoPP::RSA::PublicKey& key)
{
   CryptoPP::ByteQueue queue;

   decode(filepath, queue);
   key.BERDecodePublicKey(queue, false, queue.MaxRetrievable());
}

void rsa_sign_file(
   fs::path const & filepath,
   fs::path const & privateKeyPath,
   fs::path const & signaturePath,
   CryptoPP::RandomNumberGenerator& rng)
{
   CryptoPP::RSA::PrivateKey privateKey;
   decode_private_key(privateKeyPath, privateKey);

   CryptoPP::RSASSA_PKCS1v15_SHA_Signer signer(privateKey);

   CryptoPP::FileSource fileSource(
      filepath.c_str(),
      true,
      new CryptoPP::SignerFilter(
         rng,
         signer,
         new CryptoPP::FileSink(
            signaturePath.c_str())));
}

bool rsa_verify_file(
   fs::path const & filepath,
   fs::path const & publicKeyPath,
   fs::path const & signaturePath)
{
   CryptoPP::RSA::PublicKey publicKey;
   decode_public_key(publicKeyPath.c_str(), publicKey);

   CryptoPP::RSASSA_PKCS1v15_SHA_Verifier verifier(publicKey);

   CryptoPP::FileSource signatureFile(
      signaturePath.c_str(),
      true);

   if (signatureFile.MaxRetrievable() != verifier.SignatureLength())
      return false;

   CryptoPP::SecByteBlock signature(verifier.SignatureLength());
   signatureFile.Get(signature, signature.size());

   auto* verifierFilter = new CryptoPP::SignatureVerificationFilter(verifier);
   verifierFilter->Put(signature, verifier.SignatureLength());

   CryptoPP::FileSource fileSource(
      filepath.c_str(),
      true,
      verifierFilter);

   return verifierFilter->GetLastResult();
}

void generate_keys(
   fs::path const & privateKeyPath,
   fs::path const & publicKeyPath,
   CryptoPP::RandomNumberGenerator& rng)
{
   try
   {
      CryptoPP::RSA::PrivateKey rsaPrivate;
      rsaPrivate.GenerateRandomWithKeySize(rng, 3072);

      CryptoPP::RSA::PublicKey rsaPublic(rsaPrivate);

      encode_private_key(privateKeyPath, rsaPrivate);
      encode_public_key(publicKeyPath, rsaPublic);
   }
   catch (CryptoPP::Exception const & e)
   {
      std::cerr << e.what() << std::endl;
   }
}

int main()
{
   CryptoPP::AutoSeededRandomPool rng;

   generate_keys(
      "rsa-private.key",
      "rsa-public.key",
      rng);

   rsa_sign_file(
      "sample.txt",
      "rsa-private.key",
      "sample.sign",
      rng);

   auto success = rsa_verify_file(
      "sample.txt",
      "rsa-public.key",
      "sample.sign");

   assert(success);
}
